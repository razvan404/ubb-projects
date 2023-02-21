#!/bin/bash

if [ $# -ne 1 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./ex2.sh folder_name"
    exit -1
fi

NR_AP=0
LIST=`find $1 | grep "\.c$"`

for FILE in $LIST;
do
    LIN_C=`wc -l $FILE | cut -f1 -d" "`
    if [ $LIN_C -gt 500 ];
    then
        echo $FILE $LIN_C
        NR_AP=$((NR_AP + 1))
    fi
    if [ $NR_AP -eq 2 ];
    then
        break
    fi
done
