#!/bin/bash

function get_sum() {
	echo $1 
}

dir=$1

files=`find $dir -type 'f'`

for file_one in $files; do
	for file_two in $files; do
		if [ "$file_one" != "$file_two" ]; then
			sum_one=`get_sum $(sha1sum "$file_one")`
			sum_two=`get_sum $(sha1sum $file_two)`
#			echo "$sum_one" "$sum_two"	
			if [ "$sum_one" == "$sum_two" ]; then
				echo "$file_one" "$file_two"
			fi
		fi
	done
done
