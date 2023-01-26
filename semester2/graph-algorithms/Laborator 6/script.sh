#!/bin/bash

if [ $# -ne 2 ];
then
	echo "Invalid usage!"
	echo " Usage: ./script.sh PROBLEM_NO EXAMPLE_NO"
	exit -1
fi

./"p$1.exe" "$1/$2-in.txt" "$1.out"

echo "EXPECTED OUTPUT:"
cat "$1/$2-out.txt"
echo
echo "ACTUAL OUTPUT: "
cat "$1.out"
echo

rm "$1.out"
exit 0

