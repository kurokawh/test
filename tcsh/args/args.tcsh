#!/bin/tcsh
#
# http://www.coins.tsukuba.ac.jp/~yas/classes/syspro-2003/2003-06-23/csh.html


# ----------------------------------------------------------------------
# $1 $2 $3 ...						n番目の引数
# $argv[1] $argv[1] $argv[2] ...	n番目の引数
# $0								プログラムの名前
# $*								全引数
# $#argv							引数の数
# shift								引数のシフト
# ----------------------------------------------------------------------



echo "arg num: $#argv"

if ( $#argv > 1 ) then
    echo "num of arg is bigger than 1"
	echo "1st arg: $argv[1]"
else
    echo "num of arg is smaller than 1 or equal to 1 "
endif


