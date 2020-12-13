#! /bin/bash
module load compiler/python/3.6.0/ucs4/gnu/447 
module load pythonpackages/3.6.0/scikit-learn/0.21.2/gnu 
module load pythonpackages/3.6.0/ucs4/gnu/447/pandas/0.18.1/intel 
python reduction.py 
module unload pythonpackages/3.6.0/ucs4/gnu/447/pandas/0.18.1/intel 
module unload pythonpackages/3.6.0/scikit-learn/0.21.2/gnu 
module unload compiler/python/3.6.0/ucs4/gnu/447