import sys
#folder="~/scratch/"
folder="scratch/"
dim=[2,8]
length=[1000,10000,100000]
for d in dim:
	f=open(folder+'dim_'+str(d)+'_Rtree','r')
	output=[]	
	for l in length:
		output.append(open(folder+'RTree_dim_'+str(d)+'_'+str(l),'w'))
	i=0
	for l in f:
		for j in range(len(length)):
			if i< length[j]:
				sys.stdout=output[j]
				print(l,end="")
		i+=1
