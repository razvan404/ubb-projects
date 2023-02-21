#!/bin/bash
#shabeng

if [ $# -ne 1 ];
then
    echo "Invalid syntax!"
    echo " Usage: ./a.sh DIR"
    exit -1
fi

FILS=`find $1 -type f -perm 755`

for FIL in $FILS;
do
    while true;
    do
        printf "Are you sure you want to change the permissions for the file $FIL? [y/N]: "
        read OPT
        if [ $OPT = "y" ];
        then
            chmod 744 $FIL
            echo "Changed!"
            break
        elif [ $OPT = "N" ];
        then
            echo "Didn't changed!"
            break
        else
            echo "Invalid option! Try again!"
        fi
    done
done

