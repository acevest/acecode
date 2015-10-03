#!/usr/bin/python
# -*- coding: utf-8 -*-
# --------------------------------------------------------------------------
#   File Name:	list.py
#      Author:	Zhao Yanbai
#		Sun Jan  8 13:01:05 2012
# Description:	none
# --------------------------------------------------------------------------

L = ["Unix", "Linux", "Windows", "MaxOS"]

L.append("Android")
L.append("Symbian")
L.insert(4, "Meego")
print L
L.remove("Meego")
print L
L.append("Meego")
L.sort()
print L
L.reverse()
print L
print L[-1]

def printLine(): print "-"*80

# Use List As Stack
printLine()
print "Use List As Stack"
Stack = L
Stack.pop()
print Stack
Stack.append("WP7")
print Stack 


# Use List As Queue
from collections import deque
printLine()
print "Use List As Queue"
Queue = L
print Queue
Queue.pop(0)
print Queue
Queue.append("WP7")
print Queue

# Use Filter on List
printLine()
print "Filter"
L = range(0, 20)
print L
def funcFilter(x) : return x%2 != 0
print filter(funcFilter, L)

# Use Map on List
printLine()
print "Map"
L = range(1, 10)
print L
def funcMapA(x) : return x*x
print map(funcMapA, L)

L = range(1, 10)
def funcMapB(x, y) : return x+y
print map(funcMapB, L, L)


# Use Reduce on List
printLine()
print "Reduce"
L = range(1, 101)
print L
def sum(l) :
    def add(x, y) : return x+y
    return reduce(add, l, 0)

def trans(l) :
    def mul(x, y) : return x*10 + y
    return reduce(mul, l)
print "Sum of L is:", sum(L)
L = L[:9]
print L
print "Translate L to:", trans(L)

print "Filter"
def isOdd(n) :
    return n % 2 == 0

L = filter(isOdd, L)
print L


printLine()
L = ["   abc", "DE ", " FG ", " hi jkl    "]
print L
s = [ x.strip() for x in L]
print s
L = range(0, 21, 2)
print L
s = [ (x, x*x) for x in L]
print s
print [str(round(123/321.0, i)) for i in range(0, 15)]


a = [str(x)+'^2' for x in range(0, 10)]
b = [x*x for x in range(0,10)]

for k, v in reversed(zip(a, b)):
    print '{0}={1}'.format(k, v)

for x in range(len(a)) :
    print x,

a += b
print a


# 按下标循环
print L
for i, v in enumerate(L) :
    print i, v
