#!/usr/bin/env python
# ------------------------------------------------------------------------
#   File Name: httplib_1.py
#      Author: Zhao Yanbai
#              Sun Mar 18 13:12:09 2012
# Description: none
# ------------------------------------------------------------------------
# -*- coding: utf-8 -*-
import httplib

h = httplib.HTTPConnection("nod32.hrbeu.edu.cn")
h.putrequest('GET', '/update.ver')
h.putheader('X-NOD32-Mode', 'passive')
h.putheader('Authorization', 'Basic RUFWLWhyYmV1MDAwOjAxMjM0NTY3ODk=')
h.endheaders()
print h.getresponse().read()
h.close()
