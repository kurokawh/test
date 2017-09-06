#!/bin/bash

# loop until "q" key is pushed.
echo "loop while l is pushed"
read key
while [ "$key" = "l" ]
do
	echo "loop: $key"
	read key
done
echo "pushed: $key"

# infinit loop
# ":" means NULL command which always returns 0.
while :
do
	  echo "in the loop"
	  sleep 1
done
