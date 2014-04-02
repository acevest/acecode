#!/usr/bin/python
# -*- coding: utf-8 -*-
# --------------------------------------------------------------------------
#   File Name:	func.py
#      Author:	Zhao Yanbai
#		Tue Oct  5 19:16:52 2010
# Description:	none
# --------------------------------------------------------------------------

def printHello():
	print "Hello puppy ...";

printHello();

def printMax(a, b):
	c = a;
	if(a<b):
		c = b;
	print c, "is maximum";
	

printMax(12, 23);
a = 123;
b = 321;
printMax(a, b);

def global_func():
	global x;
	print "x is", x;
	x = 2;
	print "changed local x to", x;

x = 50;
global_func();
print "value of x is", x;

# 默认参数
def printMsg(msg, times = 1):
	print msg*times;

printMsg("hello");
printMsg("puppy ", 3);

# 关键参数
# 好处:
#	1. 不必担心参数的顺序
#	2. 只用给想要的参数赋值
def keyparam_func(a, b=5, c=10):
	print "a is", a, "b is", b, "c is", c;

keyparam_func(3, 7);
keyparam_func(44, c = 69);
keyparam_func(c = 111, a = 9);

def max(a, b):
	if a > b:
		return a;
	else:
		return b;

print max(1, 3);
print max(98, 3);

def none_return_func():
	pass;	# pass 表示空语句块, 每个函数都暗含一个return None;

none_return_func();

def swap(a, b):
	c = a;
	a = b;
	b = c;

a = 13;
b = 24;
print "before swap a =", a, "b =", b;
swap(a, b);
print "after swap a =", a, "b =", b;

# DocString
def docstring_func(x):
	'''Print x.

	x shoulde be integers or string.''';
	print x;

docstring_func(1);
print docstring_func.__doc__;
help(docstring_func);


