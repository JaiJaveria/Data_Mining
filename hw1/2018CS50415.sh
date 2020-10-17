#!/bin/bash 

if [ "$3" == "-apriori" ]; then
        ./apriori $1 $2 $4
elif [ "$3" == "-fptree" ]; then 
        ./fptree $1 $2
elif [ "$2" == "-plot" ]; then
        python3 plot.py $1
else
    echo "Wrong command"
fi