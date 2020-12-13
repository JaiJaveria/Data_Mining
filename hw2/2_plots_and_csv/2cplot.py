import pandas as pd
import matplotlib.pyplot as plt
import sys
file_name=sys.argv[1]
df=pd.read_csv(file_name)
# print(df.T)
# print(df.axis)
name=df["algo"]
df = df.rename(index = name)
df=df.drop("algo", axis=1)
# print(df)
dim=2
if "dim8" in file_name:
	dim=8
df=df.T
fig, ax = plt.subplots()
plot=df.plot(y=df.columns, kind="line", ax=ax, figsize=(18,10))
figName=(file_name.split('.')[0]).split('/')
figName=figName[len(figName)-1]
if "time" in figName:
	plt.title("time taken vs k for kNN Tool for dimension "+str(dim))
	plt.ylabel("Time Duration (in Seconds)")
if "numOp" in figName:
	plt.ylabel("Avg. Number of Operations")
	plt.title("number of Operations vs k for kNN Tool for dimension "+str(dim))
plt.xlabel("k for kNN query ")
# plt.show()
output_loc="./"
fig.savefig(output_loc+figName+".png", dpi=500, bbox_inches='tight' )
plt.close(fig)