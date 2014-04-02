#!/usr/bin/python
# -*- coding: utf-8 -*-
# --------------------------------------------------------------------------
#   File Name:	try.py
#      Author:	Zhao Yanbai
#		Wed Dec 28 21:41:17 2011
# Description:	none
# --------------------------------------------------------------------------
try:
	s = input("Enter an integer: ")
	n = int(s)
	print "valid integer entered: ", n
except NameError as nerr:
	print nerr
except ValueError as verr:
	print verr
