#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: mul.py
#      Author: Zhao Yanbai
#              Thu Oct  1 15:10:27 2015
# Description: none
# ------------------------------------------------------------------------

for j in range(1, 10) :
    for i in range(1, 10) :
        if i>j :
            continue
        print "{0}*{1}={2:<2d}\t".format(i, j, i*j),
    print ""
