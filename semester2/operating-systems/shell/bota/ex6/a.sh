#!/bin/bash

if [ $# -eq 0 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./a.sh NAM1 NAM2 ..."
    exit -1
fi

for NAM in $*;
do
    if [ -f $NAM ];
    then
        CHR=`wc -m $NAM | sed -E "s@([0-9]*)(.*)@\1@"`
        LNS=`wc -l $NAM | sed -E "s@([0-9]*)(.*)@\1@"`
        echo "File: $NAM    Characters: $CHR    Lines: $LNS"
    elif [ -d $NAM ];
    then
        FLS=`find $NAM -type f | wc -l | sed -E "s@([0-9]*)(.*)@\1@"`
        echo "Directory: $NAM   Files: $FLS"
    else
        echo "Other type: $NAM"
    fi
done

