#!/bin/bash
# run command for each argument.
#
# http://www.m-bsys.com/linux/args-loop
#

while [ "$1" != "" ]
do
	# 処理
	echo "$1"
	shift
done
