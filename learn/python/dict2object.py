#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: dict2object.py
#      Author: Zhao Yanbai
#              Wed Dec  3 18:40:09 2014
# Description: none
# ------------------------------------------------------------------------
import json

js = json.loads('{"s" : "Hello World."}')



def obj_dic(d):
    top = type('new', (object,), d)
    seqs = tuple, list, set, frozenset
    for i, j in d.items():
        if isinstance(j, dict):
            setattr(top, i, obj_dic(j))
        elif isinstance(j, seqs):
            setattr(top, i, 
            type(j)(obj_dic(sj) if isinstance(sj, dict) else sj for sj in j))
        else:
            setattr(top, i, j)

    return top


j = obj_dic(js)


print j.s
