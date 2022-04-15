#!/usr/bin/env python
# -*- coding: utf-8 -*-


# https://stackoverflow.com/questions/26985822/commenting-with-line-continuation


# multi line code by () can have comment
if (1 == 1   # cond 1
    and 2 == 2   # cond 2
    and 3 == 3): # cond 3
    print ("OK")

# BUT multi line code by \(backslash) CANNOT have comment
## this is ok
if 1 == 1 \
   and 2 == 2 \
   and 3 == 3: # cond 3
    print ("OK")

## this is error
if 1 == 1 \     # cond 1  <<< error here
   and 2 == 2 \ # cond 2
   and 3 == 3: # cond 3
    print ("OK")
