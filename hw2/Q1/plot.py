import subprocess
import timeit
import sys
from matplotlib import pyplot as plo

d=[2, 4, 8, 16, 32, 64]

L2 = [2522.13,84.5858,14.4315,5.12045,2.88072,1.89881]
Linf=[2846.88,71.0821,11.2952,4.18169,2.46858,1.7763]
L1 =[3874.28,102.142,17.3595,6.23742,3.4144,2.3202]


plo.figure()
plo.plot(d,L1,label='L1')
plo.plot(d,L2,label='L2')
plo.plot(d,Linf,label='Linf')
plo.title('Average ratio of  farthest and the nearest distances')
plo.xlabel('Dimension value (d)')
plo.ylabel('Average ratio')
plo.legend()
plo.savefig('fig.png')
plo.show(block=False)
