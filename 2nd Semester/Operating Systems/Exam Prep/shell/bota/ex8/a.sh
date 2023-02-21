#!/bin/bash

if [ $# -eq 0 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./a.sh FIL1 FIL2 ..."
    exit -1
fi

touch aux

for FIL in $*;
do
    MOST=`cat $FIL | sort | uniq -c | head -n1`
    echo "$MOST | from file $FIL" >> aux
done

cat aux | sort -r
rm aux
