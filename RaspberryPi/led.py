#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: led.py
#      Author: Zhao Yanbai
#              Sat Jan 10 21:53:49 2015
# Description: none
# ------------------------------------------------------------------------
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setup(7, GPIO.OUT)

times = 0
while True :
    if times % 2 == 0 :
        GPIO.output(7, GPIO.HIGH)
    else :
        GPIO.output(7, GPIO.LOW)
    time.sleep(1)
    times += 1
