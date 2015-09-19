#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: test.udpcli0.py
#      Author: Zhao Yanbai
#              Sat Sep 19 12:09:35 2015
# Description: none
# ------------------------------------------------------------------------
import socket

host = "127.0.0.1"
port = 9999

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.sendto(b"TEST UDP DATA\n", (host, port))
rsp, addr = s.recvfrom(4096)
print("receive data {0} from {1}:{2}".format(rsp, addr[0], addr[1]))
