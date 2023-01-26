#!/bin/bash

if [ $# -ne 1 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./a.sh DIR"
    exit -1
fi

FILES=`find $1 -type f`
TOTAL=0
COUNT=0

for FILE in $FILES;
do
    if file $FILE | grep "ASCII text";
    then
        LINS=`wc -l $FILE | sed -E "s@([0-9]*)(.*)@\1@"`
        echo "File: $FILE; Lines: $LINS"
        TOTAL=$((TOTAL + LINS))
        COUNT=$((COUNT + 1))
    fi
done

if [ $COUNT -eq 0 ];
then
    echo "No files found!"
else
    echo "Average: $((TOTAL / COUNT))"
fi

