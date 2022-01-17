# file handling
a = ''
f = ''
fn = input("filename.txt\n")  # take input from user named file
with open(fn) as fp:
    for line in fp:
        for fl in line.split():
            a = a + fl


# input
text = a


# text to ascii dec
mapped = list(map(ord, list(text)))
# print(mapped)


# int to binary map
def binaryzo(i):
    return '{0:08b}'.format(i)


# base64en
base64en = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'


# dec to bin
nmapped = ''.join(map(str, map(binaryzo, mapped)))
# print nmapped


# taking 6 bits converting to dec and then mapping with base64EN
j = 0
answer = ''
for i in range(6, len(nmapped), 6):
    temp = int(nmapped[j:i], 2)
    indexing = base64en[temp]
    answer = answer + indexing
    j = i


# Left over bits padded
limit = len(nmapped) % 6
offbit = ''
extrabit = ''
if limit:
    offbit = base64en[int(nmapped[-limit:] + '0' * (6 - limit), 2)]
    extrabit = '=' * ((6 - limit) / 2)

lll = answer + offbit + extrabit


# creating output
fn = input("filename.txt\n")  # dump output to user named file
f = open(fn, 'w')
f.write(lll)  # python will convert \n to os.linesep
f.close()
