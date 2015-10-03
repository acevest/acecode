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




# 可变参数声明形式是是在参数前面加上'*'
def Sum(*num) :
    s = 0
    for n in num :
        s += n
    return s


print Sum(1, 2, 3, 4, 5, 6)

# 如果想把一个list or tuple当多个参数传进去只需要在list or tuple前加'*'
para = [i for i in range(0, 101)]
print Sum(*para)
para = (1, 2, 3)
print Sum(*para)


# 两个'*'表示可变关键字参数
def ListParam(name, age, **kw) :
    print 'name:', name, 'age:', age, 'other:', kw

ListParam('Name.Ace', 99)
ListParam('Name.Bob', 7, city='Beijing')
ListParam('Name.Ada', 24, city='Shenzhen', gender='F', job='Engineer')
kw = {'city' : 'Chengdu', 'job' : 'IT', 'gender' : 'M'}
ListParam('Name.Jack', 9, **kw)


def Param(a, b, c=0, *args, **kw) :
    print 'a=', a, 'b=', b, 'c=', c, 'args=', args, 'kw=', kw

Param(1, 2)
Param(1, 2, c=3)
Param(1, 2, 3)
Param(1, 2, 3, 'a', 'b')
Param(1, 2, 3, 'a', 'b', 'c')
Param(1, 2, 3, 'a', 'b', 'c', pa='va', pb='vb')
Param(1, 2, *para, **kw)

# DocString
def docstring_func(x):
	'''Print x.

	x shoulde be integers or string.''';
	print x;

docstring_func(1);
print docstring_func.__doc__;
#help(docstring_func);


