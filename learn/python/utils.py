#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: utils.py
#      Author: Zhao Yanbai
#              Sat Apr 28 18:56:52 2012
# Description: none
# ------------------------------------------------------------------------

import os
import collections
print('HOME:\t'		+ os.getenv('HOME'))
print('PATH:\t'		+ os.getenv('PATH'))
print('PWD:\t'		+ os.getenv('PWD'))
print('OLDPWD:\t'	+ os.getenv('OLDPWD'))


#判断一个对象是否可以迭代
print isinstance('0xACE', collections.Iterable)
print isinstance([1, 2, 3, 4], collections.Iterable)
print isinstance(0xACE, collections.Iterable)
