#!/bin/bash

arr=()

for i in `seq 1 10`;
do
    arr+=($((2 * i)))
done

echo ${arr[*]}

