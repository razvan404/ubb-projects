#!/bin/bash

while [ $# -ge 3 ];
do
    ARG1=$1
    shift 1
    ARG2=$1
    shift 1
    ARG3=$1
    shift 1
    echo $ARG1 $ARG2 $ARG3
done
