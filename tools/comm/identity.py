#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: identity.py
#      Author: Zhao Yanbai
#              2016-12-06 17:03:17 星期二 CST
# Description: none
# ------------------------------------------------------------------------

def VerifyId(ids) :
    weight = [7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2]
    validate = ['1','0','X','9','8','7','6','5','4','3','2']
    if len(ids) != 18 :
        return False;

    Sum = 0
    for i in range(17) :
        Sum += weight[i] * int(ids[i])

    if str(ids[-1]) != validate[Sum % 11] :
        return False

    return True
