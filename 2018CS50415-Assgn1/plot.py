import subprocess
import timeit
import sys
from matplotlib import pyplot as plo

support_values = [20,25,35,50,75,90]
input = sys.argv[1]
#subprocess.run(compile_command,shell = True)

apriori_time =[]
fp_time = []

for x in support_values:
    i=timeit.default_timer()
    subprocess.run("./apriori "+input+" "+str(x)+" plot_output", shell=True)
    j=timeit.default_timer()
    apriori_time.append(j-i)

    k=timeit.default_timer()
    subprocess.run("./fptree "+input+" "+str(x), shell=True)
    l=timeit.default_timer()
    fp_time.append(l-k)

plo.figure()
plo.plot(support_values,apriori_time,label='apriori')
plo.plot(support_values,fp_time,label='fptree')
plo.title('Execution times of fpgrowth and apriori')
plo.xlabel('Support(%)')
plo.ylabel('Execution Time(s)')
plo.legend()
plo.savefig('fig.png')
plo.show(block=False)
