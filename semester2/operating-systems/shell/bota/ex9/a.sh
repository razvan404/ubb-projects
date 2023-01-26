#!/bin/bash

if [ $# -ne 1 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./a.sh DIR"
    exit -1
fi

FILS=`find $1 -type f`

for FIL in $FILS;
do
    FILNAM=`echo $FIL | sed -E "s@.*/@@"`
    if [ ${#FILNAM} -lt 8 ];
    then
        echo " $FILNAM"
        if file $FIL | grep -q "ASCII text";
        then
            head -n10 $FIL
        fi
    fi
done
