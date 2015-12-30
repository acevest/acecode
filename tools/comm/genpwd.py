#!/usr/bin/python
# -*- coding: utf-8 -*-
# --------------------------------------------------------------------------
#   File Name:	genpwd.py
#      Author:	Zhao Yanbai
#		Sat Dec 24 22:51:25 2011
# Description:	批量生成密码的工具
# --------------------------------------------------------------------------
import sys
import random

chars = "abcdefghijklmnopqrstuvwxyz" \
	 "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
	 "`1234567890-=[]\\;',./" \
	 "~!@#$%^&*()_+{}|:\"<>?"
pwdstr = ""
r = random.Random()

lenchars = len(chars)
for i in range(0, lenchars) :
    n = lenchars - i
    inx = r.randrange(n)
    pwdstr += chars[inx]
    chars = chars[:inx] + chars[inx+1:]

nargv = len(sys.argv)
if nargv < 3 or nargv > 4 :
	print 'USAGE: ', sys.argv[0], ' <minLen> <maxLen> [pwdCount]'
	exit()

if nargv == 3 :
	pwdCount = 1
else :
	pwdCount = int(sys.argv[3])

minLen = int(sys.argv[1])
maxLen = int(sys.argv[2])

if minLen > maxLen :
	print 'ERROR: minLen > maxLen'
	exit()

#print "minLen: ", minLen, "maxLen: ", maxLen, "pwdCount: ", pwdCount

for i in range(0, pwdCount) :
	pwd = ""
	pwdLen = minLen + r.randrange(maxLen-minLen+1)
	for j in range(0, pwdLen) :
		pwd += pwdstr[r.randrange(len(pwdstr))]
	print pwd
