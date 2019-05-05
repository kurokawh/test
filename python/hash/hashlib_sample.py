#! /usr/bin/env python

import hashlib

Path = 'hashlib_sample.py'

f = open(Path,'rb')
BinaryData = f.read()
f.close()

SHA1 = hashlib.sha1(BinaryData).hexdigest()
print('SHA1 :',SHA1)

MD5 = hashlib.md5(BinaryData).hexdigest()
print('MD5 :',MD5)
