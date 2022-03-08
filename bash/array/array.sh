#!/bin/bash

array=("111" "222" "333")

i=0
for e in ${array[@]}; do
    echo "array[$i] = ${e}"
	echo "${e}" > ${e}.txt
    let i++
done
