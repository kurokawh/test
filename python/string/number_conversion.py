#! /usr/bin/env python

import binascii

# hex str => int
# https://stackoverflow.com/questions/209513/convert-hex-string-to-int-in-python
na = "a"
nab = "ab"
nabc = "abc"
ia = int(na, 16)
iab = int(nab,16)
iabc = int(nabc, 16)

print(ia)
print(iab)
print(iabc)

nfi = "ffffffff"
nfl = "ffffffffffffffff"
##### "f2ab0791a132a630c26d166919f13808d19d2d02"
ifi = int(nfi, 16)
ifl = int(nfl, 16)
print(ifi)
print(ifl)

# int => hex str
# https://stackoverflow.com/questions/40123901/python-integer-to-hex-string
print(hex(iabc))
print(hex(ifi))
print(hex(ifl))

nfll = nfl + nfl
ifll = int(nfll, 16)
print(nfll)
print(ifll)
print(hex(ifll))

