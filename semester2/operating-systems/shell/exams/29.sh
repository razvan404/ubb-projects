#!/bin/bash

if [ $# -eq 0 ];
then
    echo "Numar insuficient de argumente."
    echo "Utilizare: ./29.sh file1 file2 ..."
    exit -1
fi

while true;
do
    printf "Cuvant: "
    read CUV

    if [ $CUV = "stop" ];
    then
        break
    fi

    echo ""
    for FIL in $@;
    do
        if file $FIL | grep -q "ASCII text";
        then
            echo "Fisier: $FIL"
            NRLIN=`cat $FIL | grep -c "\<${CUV}\>"`
            echo "Total linii: $NRLIN"
            PAR=$((NRLIN % 2))
            if [ $PAR -eq 0 ];
            then
                echo $CUV >> $FIL
                echo "Am adaugat o linie."
            fi
            echo ""
        else
            echo "Fisier: $FIL"
            echo "Fisierul dat nu e de tip text."
            echo ""
        fi

    done
done
