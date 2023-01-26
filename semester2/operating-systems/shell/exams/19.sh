#!/bin/bash

if [ $# -ne 3 ];
then
    echo "Invalid syntax"
    echo " Usage: ./19.sh D N U"
    exit -1
fi

D=$1
N=$2
U=$3

FILS=`ls -l $D | sed '1d' | awk -v n=$N '{if ($5 < n) {printf "%s:%s:%s\n", $3, $5, $9}}' | grep "$U:"`

for FIL in $FILS;
do
    FILNAM=`echo $FIL | cut -d":" -f3`
    echo " File $FILNAM:"
    cat $D/$FILNAM | awk '{
        for (i = 1; i <= NF; i++) {
            if ($i ~ /^g.*[aeiou]/ && $i !~ /[,.!?:;]/) {
                print $i
            }
        }
    }' | sort | uniq -c | sort -r | head -n10
done
