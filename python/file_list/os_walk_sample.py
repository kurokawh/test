#! /usr/bin/env python

import os

# search "*.xml" under current directory recursively. 
for root, dirs, files in os.walk('.'):
    for file in files:
        _, ext = os.path.splitext(file)
        if ext == '.xml':
            file_path = os.path.join(root, file)
            print('found: {}'.format(file_path))
#            with open(file_path) as f:
#                print(f.read())
#                print()


# https://www.sejuku.net/blog/63816
for curDir, dirs, files in os.walk(".."):
    print('===================')
    print("current dir: " + curDir)
    print("found dir: ")
    print(dirs)
    print("found file: ")
    print(files)
