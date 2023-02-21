#!/bin/bash

printf "Testing problem 1\n"
g++ -Wall -g -o "p1.exe" "p1.cpp" &> /dev/null
if [ $? -eq 0 ]; then
	printf "  p1.cpp build succesfully\n"
	for N in {1..7}
	do
		#valgrind --leak-check=full --error-exitcode=1 ./p1.exe "1/$N-in.txt" "1.out" &> /dev/null
		./p1.exe "1/$N-in.txt" "1.out" &> /dev/null
		if [ $? -eq 0 ]; then
			diff -sw "1/$N-out.txt" "1.out" &> /dev/null
			if [ $? -eq 0 ]; then
				printf "\ttest $N - succes!\n"
			else
				printf "\ttest $N - failed!\n"
			fi
		else
			printf "\ttest $N - leaks!\n"
		fi
	done
else
	printf "  p1.cpp build failed\n"
fi

printf "\nTesting problem 2\n"
g++ -Wall -g -o "p2.exe" "p2.cpp" &> /dev/null
if [ $? -eq 0 ]; then
	printf "  p2.cpp build succesfully\n"
	for N in {1..10}
	do
		#valgrind --leak-check=full --error-exitcode=1 ./p2.exe "2/$N-in.txt" "2.out" &> /dev/null
		./p2.exe "2/$N-in.txt" "2.out" &> /dev/null
		if [ $? -eq 0 ]; then
			diff -sw "2/$N-out.txt" "2.out" &> /dev/null
			if [ $? -eq 0 ]; then
				printf "\ttest $N - succes!\n"
			else
				printf "\ttest $N - failed!\n"
			fi
		elif [ $? -eq 1 ]; then
			printf "\ttest $N - leaks!\n"
		else
			printf "\ttest $N - failed!\n"
		fi
	done
else
	printf "  p2.cpp build failed\n"
fi

