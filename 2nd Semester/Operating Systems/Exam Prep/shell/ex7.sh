#!/bin/bash

if [ $# -ne 1 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./ex7.sh file"
fi

NAMES=`cat $1`
RESULT=""

for NAME in $NAMES;
do
    if [ -z $RESULT ];
    then
        RESULT=`printf $NAME@scs.ubbcluj.ro`
    else
        RESULT=`printf $RESULT,$NAME@scs.ubbcluj.ro`
    fi
done

echo $RESULT
