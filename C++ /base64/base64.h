int power(int x,int y) //returns x raised to power y
{
	const int mod = 1e9+7;
	int t=1;
	while(y>0)
	{
		if(y%2) y-=1,t=t*x%mod;
		else y/=2,x=x*x%mod;
	}
return t;
}

int edectobin(int a,int b,int c,int d,int e,int f) //returns 6bit binary to decimal
{
	return a*power(2,5)+b*power(2,4)+c*power(2,3)+d*power(2,2)+e*power(2,1)+f*power(2,0);
}

int ddectobin(int a,int b,int c,int d,int e,int f,int g,int h) //returns 8bit binary to decimal
{
    return a*power(2,7)+b*power(2,6)+c*power(2,5)+d*power(2,4)+e*power(2,3)+f*power(2,2)+g*power(2,1)+h*power(2,0);
}

void *encode(char *name)
{
	const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int n,i,pad,temp;
	char string[8],bin[6],c,ctemp;
	FILE *fpi, *fpo;

  	fpi = fopen(name, "r");
    fpo = fopen("temp.txt", "a");
		if (fpi == NULL)
	    {
	    	perror("input file doesn't exist.\n");
	    	return 0;
	    }		

		pad=0;
    	c = fgetc(fpi);
		while (c != EOF)
	    {	
			pad++;	
		    i=0;
		    while(i<8)
		    {
		        string[i]=c%2;
		        c/=2;
		        i++;
		    }			
	        c = fgetc(fpi);    

			for(i=0;i<8;i++)
				string[i]+=48;
			for(i=0;i<4;i++)
			{
				temp=string[i];
				string[i]=string[7-i];
				string[7-i]=temp;
			}

			for(i=0;i<8;i++)
			{
				ctemp=string[i];
				fputc(ctemp,fpo);
			}
		}

		pad = 6 - (pad*8) % 6;
		for(i=0;i<pad;i++)
			fputc('0',fpo);

	fclose(fpi);
	fclose(fpo);
	strcat(name,".enco");
	fpi = fopen("temp.txt", "r");
	fpo = fopen(name, "a");

    	c = fgetc(fpi);
		while (c != EOF)
	    {			
		    i=0;
		    while(i<6)
		    {
		        bin[i]=c-48;  
				c = fgetc(fpi);
		        i++;
		    }

    	    temp=edectobin(bin[0],bin[1],bin[2],bin[3],bin[4],bin[5]);
    	    ctemp=base64chars[temp];
			fputc(ctemp,fpo);
		}

		for(i=0;i<pad/2;i++)
			fputc('=',fpo);			

	fclose(fpi);
	fclose(fpo);
	remove("temp.txt");		
}

void *decode(char *name)
{
	const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char bin[6],string[8];
	int i,temp,pad=0,count=0;
	char ctemp,c;
	FILE *fpi, *fpo;

  	fpi = fopen(name, "r");
    fpo = fopen("temp.txt", "a");
    
		if (fpi == NULL)
	    {
	    	perror("input file doesn't exist.\n");
	    	return 0;
	    }

		c = fgetc(fpi);    
		while (c != EOF)
	    {	
	    	count++;		
			if(c == '=')
			{	
				pad++;
	            c = fgetc(fpi);    
				continue;
			}						

	        ctemp=c;
            c = fgetc(fpi);    
            
	        for(i=0;i<64;i++)
	        {
	            if(ctemp==base64chars[i])
	            {
	            	temp=i; 

	            	break;
	            }
	        }
	        
	        bin[5]=temp%2; temp/=2;
	        bin[4]=temp%2; temp/=2;
	        bin[3]=temp%2; temp/=2;
	        bin[2]=temp%2; temp/=2;
	        bin[1]=temp%2; temp/=2;
	        bin[0]=temp%2;

			for(i=0;i<6;i++)
				bin[i]+=48;	        

   			for(i=0;i<6;i++)
			{
				ctemp=bin[i];
				fputc(ctemp,fpo);
			}			
	    }

   	fclose(fpi);
	fclose(fpo);
	strcat(name,".deco");
	fpi = fopen("temp.txt", "r");
	fpo = fopen(name, "a");

    	c = fgetc(fpi);
		while (c != EOF && count!=pad*2)
	    {			
			count--;
		    i=0;
		    while(i<8)
		    {
		        string[i]=c-48;
				c = fgetc(fpi);
		        i++;
		    }

    	    temp=ddectobin(string[0],string[1],string[2],string[3],string[4],string[5],string[6],string[7]);
    	    ctemp=temp;
			fputc(ctemp,fpo);
		}	

	fclose(fpi);
	fclose(fpo);
	remove("temp.txt");
}	