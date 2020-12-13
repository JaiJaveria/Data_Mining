#! /bin/bash
module load compiler/python/3.6.0/ucs4/gnu/447 
module load pythonpackages/3.6.0/numpy/1.15.0/gnu/447 
python convert.py 
module unload compiler/python/3.6.0/ucs4/gnu/447 
module unload pythonpackages/3.6.0/numpy/1.15.0/gnu/447
