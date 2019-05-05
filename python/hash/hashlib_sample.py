#! /usr/bin/env python

import hashlib

path = 'hashlib_sample.py'

f = open(path,'rb')
binary_data = f.read()
f.close()

SHA1 = hashlib.sha1(binary_data).hexdigest()
print('SHA1 :',SHA1)

MD5 = hashlib.md5(binary_data).hexdigest()
print('MD5 :',MD5)
