#! /bin/bash
module load compiler/python/3.6.0/ucs4/gnu/447 
module load pythonpackages/3.6.0/matplotlib/3.0.2/gnu 
python plot.py 
module unload pythonpackages/3.6.0/matplotlib/3.0.2/gnu 
module unload compiler/python/3.6.0/ucs4/gnu/447