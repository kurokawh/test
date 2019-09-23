#! /usr/bin/env python

#
# https://note.nkmk.me/python-list-append-extend-insert/
#
############ append ############
l = list(range(3))
print(l)
# [0, 1, 2]

l.append(100)
print(l)
# [0, 1, 2, 100]

l.append('new')
print(l)
# [0, 1, 2, 100, 'new']

############ extend ############
l = list(range(3))
print(l)
# [0, 1, 2]

l.extend([100, 101, 102])
print(l)
# [0, 1, 2, 100, 101, 102]

l.extend((-1, -2, -3))
print(l)
# [0, 1, 2, 100, 101, 102, -1, -2, -3]

############ insert ############
l = list(range(3))
print(l)
# [0, 1, 2]

l.insert(0, 100)
print(l)
# [100, 0, 1, 2]

l.insert(-1, 200)
print(l)
# [100, 0, 1, 200, 2]



#
# https://www.sejuku.net/blog/67215
#

# 1 dimension
listA = [1] * 5
listB = [1, 2, 3, 4, 5]
 
print(listA)
print(listB)


# 2 dimension
	
list1 = [[0]*3]*2
list2 = [[0 for i in range(3)] for j in range(2)]
list3 = [[1, 2, 3], [10, 20, 30], [100, 200, 300]]
 
print(list1)
print(list2)
print(list3)
