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

# hash
h = hashlib.sha1(binary_data);
str_sha1 = h.digest()
print('digest_size:', h.digest_size)
print('block_size:', h.block_size)
print('str-len:', len(str_sha1))


# libhash
print
print('### properties in hashlib ###')
print('hashlib.algorithms:', hashlib.algorithms)
print('hashlib.algorithms_guaranteed:', hashlib.algorithms_guaranteed)
print('hashlib.algorithms_available:', hashlib.algorithms_available)
