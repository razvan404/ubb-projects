#!/bin/bash

while [ $# -gt 2 ];
do
    FIL=$1
    shift 1
    CUV=$1
    shift 1
    K=$1
    shift 1

    #cat $FIL | grep -E "(\<$CUV\>.*){$K}"
    awk -v cuv=$CUV -v kk=$K 'BEGIN { 
        }

        {
            k = 0;
            for (i = 1; i <= NF; i++) {
                if ($i == cuv) { 
                    k++;
                }
            }
            if (k == kk) {
                print $0;
            }
        } 
        
        END{

        }' fi.txt
done

