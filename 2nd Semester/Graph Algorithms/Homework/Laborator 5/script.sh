#!/bin/bash

if [ $# -ne 2 ];
then
	echo "Invalid syntax"
	echo " Usage: ./script.sh PROBL EXAMPLE"
	exit -1
fi

g++ -Wall -o "$1.exe" "main.cpp"

if [ $? -ne 0 ];
then
	echo "BUILD ERROR"
	exit -1
fi

./"$1.exe" "$1" "$1/$2-in.txt" "$1.out"

if [ $? -ne 0 ];
then
	echo "RUN ERROR"
	exit -1
fi

printf "EXCEPTED OUTPUT:\n"
cat "$1/$2-out.txt"
printf "\n\nOUTPUT:\n"
cat "$1.out"
printf "\n"
rm "$1.out"
rm "$1.exe"

