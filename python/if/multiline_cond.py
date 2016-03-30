#!/usr/bin/env python
# -*- coding: utf-8 -*-

# OK if no comment
for i in range(1, 100):
    if i % 3 == 0  \ 
        or "2" in str(i):
        print "2 or 3!: " + str(i)
    else:
        print str(i)


# ERROR if there is comment
for i in range(1, 100):
    if i % 3 == 0  \ # 3
        or "2" in str(i): # or 2
        print "2 or 3!: " + str(i)
    else:
        print str(i)
