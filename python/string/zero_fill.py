# https://note.nkmk.me/python-zero-padding/

s = '1234'
n = 1234


##### zfill() #####
s_zero = s.zfill(8)
print(s_zero)
# 00001234
print(type(s_zero))
# <class 'str'>


print(type(n))
# <class 'int'>
# print(n.zfill(8))
# AttributeError: 'int' object has no attribute 'zfill'
print(str(n).zfill(8))
# 00001234



##### rjust() #####
print(s.rjust(8, '0'))
# 00001234
print(s.ljust(8, '0'))
# 12340000
print(s.center(8, '0'))
# 00123400



##### format() #####
print(format(s, '0>8'))
# 00001234
print('Zero Padding: {:0>8}'.format(s))
# Zero Padding: 00001234
ms = '-1234'
print(format(ms, '0>8'))
# 000-1234
print('Zero Padding: {:0>8}'.format(ms))
# Zero Padding: 000-1234


print(format(n, '08'))
# 00001234
print('Zero Padding: {:08}'.format(n))
# Zero Padding: 00001234
print(format(n, '08x'))
# 000004d2
print('Zero Padding: {:08x}'.format(n))
# Zero Padding: 000004d2
mn = -1234
print(format(n, '08'))
# -0001234
print('Zero Padding: {:08}'.format(n))
# Zero Padding: -0001234
