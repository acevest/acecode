#!/usr/bin/python
# -*- coding: utf-8 -*-
# --------------------------------------------------------------------------
#   File Name:	set.py
#      Author:	Zhao Yanbai
#		Sun Jan  8 15:35:09 2012
# Description:	none
# --------------------------------------------------------------------------


L = ['apple', 'banana', 'orange', 'orange', 'banana']
print "List L: ", L
S = set(L)
print "Set S:", S


a = set('hello python world')
b = set('hello world')
print "Set a: ", a
print "Set b: ", b
print "a-b: ", a-b
print "a|b: ", a|b
print "a&b: ", a&b
print "a^b: ", a^b


Set = {'apple', 'orange', 'apple', 'pear', 'orange', 'banana'}
print(Set)


#Empty Set
EmptySet = set() # not { }
