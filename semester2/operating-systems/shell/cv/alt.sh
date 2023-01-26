#!/bin/bash


while printf "Give 2 words: " && read U P && [ $U != "stop" ];
do
    echo " First: $U"
    echo " Second: $P"
done
