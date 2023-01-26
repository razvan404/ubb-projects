#!/bin/bash

LIST=`cat who.fake | cut -d" " -f1`

for EL in $LIST;
do
    NR_AP=`cat ps.fake | grep "^$EL" | wc -l`
    echo $EL $NR_AP
done

