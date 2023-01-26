#!/bin/bash

if [ $# -ne 1 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./script.sh FILE"
    exit 1
fi

WHERE=$1
find $WHERE > lines

while read line;
do
    if [ -f $line ];
    then
        grep -E -n "^.*cat.*\.txt$" $line | sed "s@.*/@@"
    fi
done < lines
rm lines

