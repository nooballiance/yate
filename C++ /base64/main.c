#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"

int main(void)
{
	int n;
	char name[20];

	printf("\nOptions> 1. Encoding 0. Decoding \n");
	scanf("%d",&n); 
	printf("Enter file name> ");
	scanf("%s",name); 

	if(n)
		encode(&name[0]);
	else
		decode(&name[0]);

return 0;
}