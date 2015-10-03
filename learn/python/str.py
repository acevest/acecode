#!/usr/bin/python
# -*- coding: utf-8 -*-
# --------------------------------------------------------------------------
#   File Name:	str.py
#      Author:	Zhao Yanbai
#		Wed Dec 28 22:28:49 2011
# Description:	none
# --------------------------------------------------------------------------

import math

s = "The quick brown fox jumps over the lazy dog"
print "s: ", s
print "s[0]: ", s[0]
print "s[len(s)-1]: ", s[len(s)-1]
print "s[7:14]: ", s[7:14]
print "s[0:len(s)-1]: ", s[0:len(s)-1]
print "s[-len(s):-1]: ", s[-len(s):-1]
print "s[-3:]: ", s[-3:]
print "s[0:len(s)-1:2]: ", s[0:len(s)-1:2]
print "s[-1:0:-1]: ", s[-1:0:-1]

a = "double line " +\
    "second line"
b = (   "first line "
        "second line")
print a
print b


print "{key} : {value}".format(key="hahaha", value="wawawa")


stock = ["paper", "envelopes",  "notepads", "pens", "paper clips"]
print "We have {0[1]} and {0[2]} in stock".format(stock)

d = dict(animal="elephant", weight=12000)
print "The {0[animal]} weighs {0[weight]}kg".format(d)

print "math.pi = {0.pi}".format(math)

print "{} {} {}".format('Apple', 'Google', 'Microsoft')


# 当前还在作用域范围肉的局部变量是可以通过内置的locals函数访问
# 该函数会返回一个字典，键名是变量名，字典的值则是对变量值的引用
# 现在可以使用映射拆分将字典提供给str.format()方法
# 映射拆分操作符为** 可应用于映射（比如字典）来产生一个适合于传递
# 给函数的键-值列表
Apple = 1
Google = 2
Microsoft = 3
print "{Apple} {Google} {Microsoft}".format(**locals())

#r'' 表示''内的内容不用转义
print r'a\nb\tc'
print r"a\n'b\tc"

print r'''abc
c\tefghijlk\nfff
ffff'''

print ord('A')
print chr(65)
