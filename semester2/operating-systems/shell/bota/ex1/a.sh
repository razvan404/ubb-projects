#!/bin/bash

if [ $# -ne 1 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./a.sh N"
    exit -1
fi

for X in `seq 1 $1`;
do
    cat passwd.fake | head -n$[X+5] | tail -n5 > file_$X.txt
done

