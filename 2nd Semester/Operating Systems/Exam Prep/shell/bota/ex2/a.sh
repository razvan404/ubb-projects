#!/bin/bash

if [ $# -ne 1 ];
then
    echo "Invalid syntax"
    echo " Usage: ./a.sh dir"
    exit -1
fi

if [ -d $1 ];
then
    FILES=`find $1 -type f`
else
    echo "Invalid syntax"
    echo " Usage: ./a.sh dir"
    exit -1
fi

for FILE in $FILES;
do
    if file $FILE | grep -q "ASCII text";
    then
        FILTXT=`echo $FILE | sed -E "s@.*/@@"`
        echo " File $FILTXT:"
        cat $FILE | head -n3
        echo ""
    fi
done
