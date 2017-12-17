#!/bin/bash
# http://sweng.web.fc2.com/ja/program/bash/bash-compare-string.html
 
foo=aaa
var=aaa
 
if [ ${foo} = ${var} ]; then
    echo "equal"
fi
# same result
#if [ $foo = $var ]; then
#    echo "equal"
#fi

if [ ${foo} != "bbb" ]; then
    echo "not equal"
fi

# string length
if [ -n ${foo} ]; then # 変数fooのサイズが1以上であれば真
    echo "not null"
fi
 
foo=
if [ -z ${foo} ]; then # 変数fooのサイズが0であれば真
    echo "null"
fi



# check if string is contained in a file.
text="hoge"
if [ $(echo $text | grep -e 'h') ]; then
    echo "hoge include h"
else
    echo "hoge doesn't include h"
fi
if [ $(echo $text | grep -e 'a') ]; then
    echo "hoge include a"
else
    echo "hoge doesn't include a"
fi
