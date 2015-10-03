#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: decorator.py
#      Author: Zhao Yanbai
#              Fri Oct  2 19:00:55 2015
# Description: 装饰器
# ------------------------------------------------------------------------

import time
import functools

def now() :
    print time.asctime()

########################
def now0() :
    now()

now0()
print now0.__name__


########################
def log1(func) :
    def wrapper1(*args, **kw) :
        print '[This is the decorator] > ',
        return func(*args, **kw)
    return wrapper1

@log1
def now1() :
    now()

now1()
print now1.__name__

########################
def log2(param) :
    # 先实现处理传入参数的函数
    # 再实现装饰器
    def decorator(func) :
        def wrapper2(*args, **kw) :
            print '[This is the parameter {0}] >'.format(param),
            print '[This is the decorator] >',
            return func(*args, **kw)
        return wrapper2
    return decorator

@log2('LOG2')  #等价于 log2('LOG2')(now2)
def now2() :
    now()

now2()
print now2.__name__



########################
# 让装饰器不影响函数名字
def log3(func) :
    @functools.wraps(func)
    def wrapper3(*args, **kw) :
        print '[This is the decorator] >',
        return func(*args, **kw)
    return wrapper3

@log3
def now3() :
    now()

now3()
print now3.__name__
