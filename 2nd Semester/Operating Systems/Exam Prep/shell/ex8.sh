#!/bin/bash
#shabeng

if [ $# -ne 1 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./ex8.sh DIR"
    exit
fi

FILS=`find $1 -type f`

for FIL1 in $FILS;
do
    for FIL2 in $FILS;
    do
        MD1=`sha1sum $FIL1 | sed -E "s@([^ ]*)(.*)@\1@"`
        MD2=`sha1sum $FIL2 | sed -E "s@([^ ]*)(.*)@\1@"`
        if [[ $FIL1 != $FIL2 ]] && [[ $FIL1 < $FIL2 ]] && [[ $MD1 == $MD2 ]];
        then
            echo "File: $FIL1 ($MD1) | Duplicate: $FIL2 ($MD2)"
        fi
    done
done

