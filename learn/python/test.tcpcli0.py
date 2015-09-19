#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: test.tcpcli0.py
#      Author: Zhao Yanbai
#              Sat Sep 19 11:57:00 2015
# Description: none
# ------------------------------------------------------------------------
import socket

host = "127.0.0.1"
port = 9999

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))
s.send(b"TCP CLIENT TEST DATA\n")
rsp = s.recv(4096)
print(rsp)
