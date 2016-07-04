#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: mi.py
#      Author: Zhao Yanbai
#              2016-07-04 22:36:34 Monday CST
# Description: none
# ------------------------------------------------------------------------

import datetime
import time
import mibanda
import sys

def main() :
    if len(sys.argv) != 2 :
        print("{0} <mac_address>".format(sys.argv[0]))
        sys.exit()

    macAddr = sys.argv[1]

    device = mibanda.BandDevice(macAddr, "MI")
    device.connect()
    print "Address:", device.getAddress()
    print "Name:", device.getName()
    bi = device.getBatteryInfo()
    print "BatteryInfo. Status:", bi.status, " Level:", bi.level, " Charge Counter:", bi.charge_counter, " Last Charge:", bi.last_charged

    print "Steps:", device.getSteps()
    di = device.getDeviceInfo()
    print "DeviceInfo:", di.firmware_version

    print "SetUserInfo"
    device.setUserInfo(27182818, True, 25, 123, 45, 0, "Ace")
    print "Finished"
    t= datetime.datetime.now() + datetime.timedelta(seconds=100)
    device.setAlarm(enable=1, number=0, when=t, smart=0, repeat=0) 


if __name__ == "__main__" :
    main()
