#first is the data file , 2nd hee length
import random
import sys
arr=[]
while(len(arr)!=100):
	a=int(random.random()*int(sys.argv[2]))
	if a not in arr:
		arr.append(a)
f=open(sys.argv[1],'r')
i=0
for l in f:
	if i in arr:
		a=l.split()
		a[0]='2'
		for j in a:
			print(j, end=" ")
		print()
	i+=1

