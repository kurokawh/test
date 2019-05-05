#! /usr/bin/env python

import hashlib

path = 'hashlib_sample.py'

f = open(path,'rb')
binary_data = f.read()
f.close()

hex_sha1 = hashlib.sha1(binary_data).hexdigest()
print('SHA1 :', hex_sha1)

hex_md5 = hashlib.md5(binary_data).hexdigest()
print('MD5 :', hex_md5)
