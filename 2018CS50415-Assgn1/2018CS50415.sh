#!/bin/bash 

if [ "$3" == "-apriori" ]; then
        ./apriori $1 $2 $4
elif [ "$3" == "-fptree" ]; then 
        ./fptree $1 $2 > $4
elif [ "$2" == "-plot" ]; then
        module load pythonpackages/3.6.0/matplotlib/3.0.2/gnu
        python3 plot.py $1
        rm plot_output
        module unload pythonpackages/3.6.0/matplotlib/3.0.2/gnu
else
    echo "Wrong command"
fi
