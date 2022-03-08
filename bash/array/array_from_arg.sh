#!/bin/bash


i=0 # $0 is script name
for e in $@; do
    echo "array[$i] = ${e}"
	echo "${e}" > ${e}.txt
    let i++
done
