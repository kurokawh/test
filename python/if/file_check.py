#! /usr/bin/env python

import os

def check(path):
    print ("checking...: " + path)
    if os.path.exists(path):
        print("EXIST!")
    else:
        print("NOT EXIST!")

check("file_check.py")
check("xxx.txt")
