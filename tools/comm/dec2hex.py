#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: dec2hex.py
#      Author: Zhao Yanbai
#              Tue Apr 28 15:00:56 2015
# Description: none
# ------------------------------------------------------------------------

while True :
	n = raw_input("Input Decimal: ")
	hexs = "{0:X}".format(int(n))
	print hexs
