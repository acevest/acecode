#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: scapy.1.py
#      Author: Zhao Yanbai
#              Sun Sep 27 11:12:24 2015
# Description: none
# ------------------------------------------------------------------------

from scapy.all import *

def packet_callback(packet) :
    print packet.show()

scapy.all.sniff(filter='tcp', prn=packet_callback, store=0)
