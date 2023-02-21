#!/bin/bash

if [ $# -ne 1 ];
then
    echo "Numar insuficient de argumente."
    echo "Utilizare: ./script.sh fisier_cuvinte"
    exit -1
fi

CUV=$1

while true;
do
    printf "Introdu N, introdu 0 dupa ce ai introdus numarul corect: "
    read N2
    if [ $N2 -eq 0 ];
    then
        break
    else
        N=$N2
    fi
done

printf "Introdu numele de fisier: "
read FIL

rm -f $FIL
touch $FIL

CRNT=0
STR=""
while read line;
do
    if [ $CRNT -lt $N ];
    then
        STR=`printf "%s %s " ${STR} ${line}`
        CRNT=$((CRNT + 1))
    else
        echo $STR >> $FIL
        CRNT=1
        STR=$line
    fi
done < $CUV

if ! [ -z $STR ];
then
    echo $STR >> $FIL
fi

echo "Fisier: $FIL"
NRL=`wc -l $FIL | cut -d" " -f1`
NRC=`wc -w $FIL | cut -d" " -f1`
NRM=`wc -m $FIL | cut -d" " -f1`
echo "Linii: $NRL Cuvinte: $NRC Caractere: $NRM"

