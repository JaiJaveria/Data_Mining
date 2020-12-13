import sys
file=open(sys.argv[1],'r')
i=0
for l in file:
	t=l.split()
	print(1,end=" ")
	print(i, end=" ")
	i+=1
	for a in t:
		print(a,end=" ")
	for a in t:
		print(float(a)+0.01, end=" ")
	print()
