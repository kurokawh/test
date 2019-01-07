#!/bin/bash
# https://qiita.com/blackenedgold/items/4f91a174e0f63ee42699
# http://code.i-harness.com/ja/q/4b12f

# STATE=""
if [ -n "$STATE" ] ; then
	echo "STATE is set: $STATE"
else 
	echo "STATE is zero-length or undefined: $STATE"
fi

if [ -z "$STATE" ]; then
    echo "STATE is zero-length or undefined: $STATE"
else
	echo "STATE is set: $STATE"
fi  

if [ "${STATE}" = "" ]; then
    echo "STATE is zero-length or undefined: $STATE"
else
	echo "STATE is set: $STATE"
fi

### only this statement can check if "" or undefined ###
if ${STATE+:} false; then
    echo "STATE is defined: $STATE"
else
	echo "STATE is not defined: $STATE"
fi
