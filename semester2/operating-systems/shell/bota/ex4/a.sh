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
    if cat $FILE | grep -qE "[0-9]{5}";
    then
        FILNAME=`echo $FILE | sed "s@.*/@@"`
        echo $FILNAME
    fi
done

