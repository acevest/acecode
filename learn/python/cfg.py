#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: cfg.py
#      Author: Zhao Yanbai
#              Thu May 10 09:38:22 2012
# Description: none
# ------------------------------------------------------------------------

import ConfigParser
import os
import sys


cp = ConfigParser.ConfigParser()

cp.read("./cfg.conf")


print cp.get("db", "name")
print cp.get("db", "pwd")
