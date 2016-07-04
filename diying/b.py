#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: ble.py
#      Author: Zhao Yanbai
#              2016-07-04 22:42:30 Monday CST
# Description: none
# ------------------------------------------------------------------------
import struct
import time
import binascii
import bluepy.btle as btle

class MyDelegate(btle.DefaultDelegate):
    def __init__(self):
        btle.DefaultDelegate.__init__(self)

    def handleNotification(self, cHandle, data):
        print("cHandle:", hex(cHandle), " Data:", data)

def uuid2str(uuid) :
    s = binascii.b2a_hex(uuid)
    return "-".join([s[0:8], s[8:12], s[12:16], s[16:20], s[20:32]])

def barline(title) :
    s = title
    s += "-"*(80-len(title))
    print(s)

p = btle.Peripheral("C8:0F:10:6A:B1:F0", btle.ADDR_TYPE_PUBLIC, 0)
p.withDelegate( MyDelegate() )


Services = p.getServices()
Characteristics = p.getCharacteristics()


barline("Services")
for s in Services :
    print("{0} {1}".format(uuid2str(s.uuid.binVal), s.uuid.getCommonName()))

barline("Characteristics")
ch = None
och = None
for c in Characteristics :
    print("{0} {1:4} {2:>5} {3:18} {4}".format(uuid2str(c.uuid.binVal), hex(c.getHandle()), str(c.supportsRead()), c.propertiesToString(), c.uuid.getCommonName()))
    if  c.uuid.getCommonName() == "ff04" :
        ch = c

    if c.uuid.getCommonName() == 'Alert Level' :
        print binascii.b2a_hex(c.read())
        och = c

p.disconnect()

