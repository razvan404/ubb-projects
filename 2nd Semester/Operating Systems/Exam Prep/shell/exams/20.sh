#!/bin/bash
#shabeng

if [ $# -le 1 ];
then
    echo "Numar insuficient de argumente."
    echo "Utilizare: ./practic.sh PERM dir1 dir2 ..."
    exit -1
fi

PER=$1

shift 1
echo "Permisiuni: $PER"

for DIR in $*;
do
    if [ -d $DIR ];
    then
        echo "Director: $DIR"
        FILS=`ls -l $DIR | sed '1d' | awk '{
            printf "%s:%s\n", $1, $9;
        }' | grep "\-$PER"`
        for FIL in $FILS;
        do
            PER2=`echo $FIL | cut -d":" -f1`
            FILNAM=`echo $FIL | cut -d":" -f2`
            FILLOC=`echo ${DIR}/${FILNAM}`
            echo " Fisier: $FILLOC" 
            echo " Permisiuni: $PER2"
            FILBAK=`echo ${FILLOC}.bak`
            
            rm -f $FILBAK
            cp $FILLOC $FILBAK

            chmod 400 $FILBAK
            PER3=`ls -l $FILBAK | cut -d" " -f1` 

            echo " Copie: $FILBAK"
            echo " Permisiuni: $PER3" 
        done
    else
        echo "Director: $DIR"
        echo " Directorul dat nu exista."
    fi
done
