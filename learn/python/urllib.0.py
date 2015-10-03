#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: urllib.0.py
#      Author: Zhao Yanbai
#              Thu Oct  1 12:15:20 2015
# Description: none
# ------------------------------------------------------------------------
import urllib
import urllib2
import urlparse

url =  "http://192.168.1.101:8080/sqli/Less-1/index.php?id=1"

print urlparse.urlsplit(url)

request = urllib2.Request(url)
response = urllib2.urlopen(request)


print response.read()

response.close()
