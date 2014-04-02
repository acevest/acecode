#!/usr/bin/python
# -*- coding: utf-8 -*-
print 'Hello World'
print "Hello World"
print 'He	llo\nWorld' # 原样保留空白：空格制表符
print '''
hello
world
....'''
print "Hello \
World"

# 可以在''' '''之间自由使用 ' 和 "
print ''' puppy said: "money is 'very' important". ''';

print 'hello\
puppy';

print r"sssss\n"; # 加r或R指示为自然字符串

print u"Unicode 字符串";

print "大江东去 <<要加# -*- coding: utf-8 -*- 且必需在第一或二行"

