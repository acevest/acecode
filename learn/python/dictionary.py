#!/usr/bin/python
# -*- coding: utf-8 -*-
# --------------------------------------------------------------------------
#   File Name:	dictionary.py
#      Author:	Zhao Yanbai
#		Sun Jan  8 15:46:47 2012
# Description:	none
# --------------------------------------------------------------------------
import random
D = { 'apple':'40', 'banana':'80', 'orange':30 }
print D
print "Keys of D : ", D.keys()
print "Values of D: ",
for _ in D.keys() :
    print D[_],

print "\n", 'apple' in D
print '40' in D

D = dict([('China', 13), ('Janpan', 4), ('American', 3), ('Russian', 1), ('England', 1.2)])
print D

for k, v in D.iteritems() :
    print "(", k, ":", v, ")"

D = dict([('S'+str(x).zfill(9), random.randint(0, 10E8)) for x in range(0, 11)])
print D

for name, value in D.items() :
    print "{0:10} : {1:10d}".format(name, value)

D = {x:x**2 for x in range(10)}
print(D)

D = dict(a=1, b=2, c=3)
print D

print "-"*72
import os
file_sz = {name : os.path.getsize(name) for name in os.listdir(".")}
for item in file_sz.items() :
    print "{1}:\t{0}".format(item[0], item[1])

x = dict()

for i in range(0, 10) :
    x[i] = x.get(i, i)

for i in sorted(x.keys()) :
    print x[i],

print("")

# Another Make Empty Dictionary Method
x = { }

for i in range(0, 10) :
    x[i] = x.get(i, i)

for i in sorted(x.keys()) :
    print x[i],
