#! /bin/bash
module load compiler/gcc/9.1.0 
./glove $1 $2 
module unload compiler/gcc/9.1.0
