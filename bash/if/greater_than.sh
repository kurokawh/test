#!/bin/bash

var1=1
var2=2


#### >
if [ $var2 -gt $var1 ] ; then
  echo "var2はvar1より大きい"
else
  echo "var2はvar1以下"
fi


#### >=
if [ $var2 -ge $var1 ] ; then
  echo "var2はvar1以上"
else
  echo "var2はvar1より小さい"
fi


#### <
if [ $var1 -lt $var2 ] ; then
  echo "var1はvar2より小さい"
else
  echo "var1はvar2以上"
fi


#### <=
if [ $var1 -le $var2 ] ; then
  echo "var1はvar2以下"
else
  echo "var1はvar2より大きい"
fi
