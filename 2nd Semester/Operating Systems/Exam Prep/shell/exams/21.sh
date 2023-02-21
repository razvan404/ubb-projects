#!/bin/bash
#shabeng

if [ $# -ne 2 ];
then
    echo "Numar insuficient de argumente."
    echo "Utilizare: ./21.sh fisier_comenzi fisier_propozitii"
    exit -1
fi

cp 21.bak 21.prop

CMD=$1
PROP=$2

while read C1 C2 C3 C4;
do
    if [ $C1 = "INSERT" ] && [ $C2 = "LINE" ];
    then
        touch ${PROP}.func
        cat $PROP | sed -E "${C3}"'i'"$C4" > ${PROP}.func
        rm $PROP
        cp ${PROP}.func $PROP
        rm ${PROP}.func
    elif [ $C1 = "REPLACE" ] && [ $C2 = "CHAR" ];
    then
        touch ${PROP}.func
        if [ -z $C4 ];
        then
            cat $PROP | sed "s@$C3@ @g" > ${PROP}.func
        else
            cat $PROP | sed -E "s@$C3@$C4@g" > ${PROP}.func
        fi
        rm $PROP
        cp ${PROP}.func $PROP
        rm ${PROP}.func
    elif [ $C1 = "REPLACE" ] && [ $C2 = "WORD" ];
    then
        touch ${PROP}.func
        if [ -z $C4 ];
        then
            cat $PROP | sed "s@$C3@ @g" > ${PROP}.func
        else
            cat $PROP | sed -E "s@$C3@$C4@g" > ${PROP}.func
        fi
        rm $PROP
        cp ${PROP}.func $PROP
        rm ${PROP}.func
    elif [ $C1 = "APPEND" ] && [ $C2 = "LINE" ];
    then
        touch ${PROP}.func
        cat $PROP | sed -E '$a'"$C3" > ${PROP}.func
        rm $PROP
        cp ${PROP}.func $PROP
        rm ${PROP}.func

    fi

done < $CMD
