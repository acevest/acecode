#!/usr/bin/python
# -*- coding: utf-8 -*-
# --------------------------------------------------------------------------
#   File Name:	tuple.py
#      Author:	Zhao Yanbai
#		Wed Dec 28 23:36:27 2011
# Description:	none
# --------------------------------------------------------------------------
ta = "black", "green", "red", "yellow", "blue", "grey", "white", "red"
print "ta: ", ta
print "ta[2]: ", ta[2]
print "ta.count('red'): ", ta.count('red')
print "ta.index('blue'): ", ta.index('blue')

for x in ta:
	print x


print "ta[:2] + ('black',) + ta[0:]: ", ta[:2] + ('black',) + ta[0:]

a,b = (1, 2)

print a
print b


eyes = ('brown', 'hazel', 'amber', 'green', 'blue', 'gray')
colors = (ta, eyes)
print colors[1][3:-1] # -1 是表示最后一个元素而不是倒数第二个元素
print eyes
print eyes[1:5]

a,b = (1, 2)
print "a=", a, "b=", b
a,b = (b,a)
print "a=", a, "b=", b

# 遍历tuple中的偶数下标元素的方法
for i in range(0, len(eyes), 2) :
	print eyes[i],

empty = ()
print len(empty)
singleton = 'hello', # <--- note comma
print singleton
singleton = ('singleton string',)
print singleton

t = ('x value', 'y value', 'z value')
x, y, z = t
print "x: ", x, "y: ", y, "z: ", z


# 命名元组
import collections
Sale = collections.namedtuple("xxx", "productid customerid date quantity price")
sales = []
sales.append(Sale(249, 254, '2008-09-14', 3, 7.99))
sales.append(Sale(250, 256, '2008-09-21', 3, 3.98))

total = 0;
for sale in sales :
    total += sale.quantity * sale.price

print "Total ${0:.2f}".format(total)

for sale in sales :
    print "{0.productid}\t{0.customerid}\t{0.date}\t{0.quantity}\t{0.price}".format(sale)

print "-"*72

for sale in sales :
    print "{productid}\t{customerid}\t{date}\t{quantity}\t{price}".format(**sale._asdict())
