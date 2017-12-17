#!/bin/bash

# -w set digit number 0001-1000 (equal width).
for NUM in `seq -w 1000`
do
    echo "id-${NUM}"
done
