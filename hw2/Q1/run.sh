#! /bin/bash
module load compiler/gcc/9.1.0 
./main_q1 $1 $2 
module unload compiler/gcc/9.1.0 