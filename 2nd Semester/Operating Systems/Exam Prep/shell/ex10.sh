#!/bin/bash

month=`date +%m`
year=`date +%Y`

date_start=`echo ${year}-${month}-01`
date_end=`echo ${year}-${month}-31`

last -s"$date_start" -t"$date_end" | while read line; do
	echo $line
done
