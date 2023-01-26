#!/bin/bash

if [ $# -ne 1 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./a.sh DIR"
    exit -1
fi

FILES=`find $1 -type f`

for FILE in $FILES;
do
    if file $FILE | grep -q "ASCII text";
    then
        WRDS=`wc -l $FILE | sed -E "s@([0-9]*)(.*)@\1@"`
        echo "  File: $FILE, Lines: $WRDS"
        if [ $WRDS -lt 10 ];
        then
            cat $FILE
        else
            echo " First 5 lines:"
            head -n5 $FILE
            echo " Last 5 lines:"
            tail -n5 $FILE
        fi
        echo ""
    fi
done
