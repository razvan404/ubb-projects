#!/bin/bash
#shabeng

if [ $# -ne 1 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./ex3.sh DIR"
    exit -1
fi

FILS=`find $1 -type f`
for FIL in $FILS;
do
    if echo $FIL | grep -q ".log$";
    then
        cat $FIL | sort -o $FIL
    fi
done

