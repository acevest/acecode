#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: Sensors.py
#      Author: Zhao Yanbai
#              Thu Oct 30 14:46:58 2014
# Description: none
# ------------------------------------------------------------------------

import time
import serial
import os
import commands
import config
from utils import * 

log = CreateLogger(config.ACE_GLOBAL_LOG_PATH)

s = serial.Serial('/dev/ttyACM0', 9600)

ApiKey = 'c2ac9bff44b29c8f3edca022ed621aa9'
class Sensor :
    def __init__(self, Name, url) :
        self.Name   = Name
        self.Url    = url
        self.LastTs = 0
        self.Value  = 0

Map = { }

SensorList = [Sensor('Light', 'http://api.yeelink.net/v1.0/device/15328/sensor/26264/datapoints'),
              Sensor('Temperature', 'http://api.yeelink.net/v1.0/device/15328/sensor/26256/datapoints')]

for x in SensorList :
    Map[x.Name] = x

while True :
    line = s.readline().strip()

    if line[0] != '>' :
        continue

    log.info(line)

    (name, value) = line[1:].strip().split(': ')
    if Map.get(name, None) == None :
        continue

    if int(time.time()) - Map[name].LastTs < 10 :
        continue

    log.info('Prepare to Report')

    Map[name].LastTs = int(time.time())
    Map[name].Value  = float(value)

    json = '{"value":%f}' % Map[name].Value
    fd = open('datafile.txt', 'w+')
    fd.write(json + '\n')
    fd.close()

    cmd = 'curl --request POST --data-binary @datafile.txt --header "U-ApiKey: '+ApiKey+'" ' + Map[name].Url
    output = commands.getoutput(cmd)
    log.info(output)

