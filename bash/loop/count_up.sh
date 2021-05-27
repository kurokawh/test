#!/bin/bash
# https://qiita.com/aonisai/items/6b276ae0a9ced007640f

count=0
while true
do
  echo $count
  count=`expr $count + 1`
  if [ $count -eq 10 ]; then
    exit 0
  fi
done
