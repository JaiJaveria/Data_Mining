#!/usr/bin/python

import sys
import struct
import numpy as np

matrix = []
i = 0
with open('../../../../hw2/input8.txt', 'r') as inf:
    with open('dataset/image82.dat', 'wb') as ouf:
        counter = 0
        for line in inf:
            row = [float(x) for x in line.split()]
            
            ouf.write(struct.pack('i', len(row)))
            ouf.write(struct.pack('%sf' % len(row), *row))
            counter += 1
            matrix.append(np.array(row, dtype=np.float32))
            if counter % 10000 == 0:
                sys.stdout.write('%d points processed...\n' % counter)
            i+=1
            if i==10000:
                break
np.save('dataset/image82', np.array(matrix))
