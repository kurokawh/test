#!/bin/sh
# $0 objname < in > out
#
# read binary data from standard input.
# then output C array definition to standard output.
# arg 1 is the name of array.
#
objname=${1:-objname}
od -A n -v -t x1 | sed -e '1i\
const unsigned char '$objname'[] = {
s/\([0-9a-f][0-9a-f]\) */0x\1,/g
$s/,$//
$a\
};
'
