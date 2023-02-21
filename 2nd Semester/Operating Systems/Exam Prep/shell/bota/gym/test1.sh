#!/bin/bash

while printf "Give words: " && read p1 p2;
do
    echo " first: $p1, second: $p2"
    if [ $p1 = "stop" ];
    then
        break
    fi
done
