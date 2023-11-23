#!/bin/bash
sample_folder="testset"

sorted=0
timer=0

if [ "$1" = "-a" ]
then
    algo="$2"
fi

if [ "$3" = "-e" ]
then
    ex="$4"
fi

if [ "$5" = "-p" -o "$6" = "-p" ]
then
    sorted=1
fi

if [ "$5" = "-t" -o "$6" = "-t" ]
then
    timer=1
fi

# sort -n -c permet de regarder si notre output est trié
size=$(basename "$ex" | cut -d_ -f2)
max=$(basename "$ex" | cut -d_ -f3)

echo -e "Algo: $algo \nFile: $ex \nSize: $size \nMax: $max\n"

if [ $algo = "counting" ]
then
    t=$(./main cs $ex $max)
fi

if [ $algo = "quick" ]
then
    t=$(./main qs $ex 1 false)
fi

if [ $algo = "quickSeuil" ]
then
    t=$(./main qs $ex 9 false)
fi

if [ $algo = "quickRandomSeuil" ]
then
    t=$(./main qs $ex 9 true)
fi

if [ $timer = 1 ]
then
    echo -e "Time: $t\n"
fi



# t=$(./tp.sh -e ./${ex_folder}/${testset_folder}/${ex} -a $algo -t)

# ./tp.sh -e ./${ex} -a $algo -p | sort -n -c


