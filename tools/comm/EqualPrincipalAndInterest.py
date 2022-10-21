#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: EqualPrincipalAndInterest.py
#      Author: Zhao Yanbai
#              2022-05-25 18:36:12 Wednesday CST
# Description: none
# ------------------------------------------------------------------------

import math

total = 420*10000
year=30
yearRate = 0.0588


monthCount = year * 12
monthRate = yearRate / 12.0



r = math.pow(1+monthRate, monthCount)

X = total*monthRate*r / (r - 1)

X = round(X, 2)

print(X)
