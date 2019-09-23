#! /usr/bin/env python

# e.g.
# > python glob_sample.py "../*/*py"

import sys
import glob

# https://docs.python.org/ja/2.7/library/glob.html?highlight=glob%20glob#glob.glob
# https://hibiki-press.tech/learn_prog/python/os-listdir-glob-glob-os-wal/1323
# 

args = sys.argv

print("arg[1]: " + args[1])
file_list = glob.glob(args[1])
print(file_list)
