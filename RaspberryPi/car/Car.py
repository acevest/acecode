#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys 
import time
import RPi.GPIO as GPIO

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

class Motor :
    def __init__(self, PinA, PinB) :
        self.PinA = PinA
        self.PinB = PinB

        self.Setup()

        self.Stop()

    def Setup(self) :
        GPIO.setup(self.PinA, GPIO.OUT)
        GPIO.setup(self.PinB, GPIO.OUT)

    def Forward(self) : 
        GPIO.output(self.PinA, GPIO.HIGH)
        GPIO.output(self.PinB, GPIO.LOW)

    def Backward(self) :
        GPIO.output(self.PinA, GPIO.LOW)
        GPIO.output(self.PinB, GPIO.HIGH)
        
    def Stop(self) :
        GPIO.output(self.PinA, GPIO.LOW)
        GPIO.output(self.PinB, GPIO.LOW)


class Car() :
    def __init__(self) :
        self.ma = Motor(3,  5)
        self.mb = Motor(7,  11)
        self.mc = Motor(13, 15)
        self.md = Motor(19, 21)
    def Forward(self) :
        self.ma.Forward()
        self.mb.Forward()
        self.mc.Forward()
        self.md.Forward()
    def Backward(self) :
        self.ma.Backward()
        self.mb.Backward()
        self.mc.Backward()
        self.md.Backward()
    def TurnLeft(self) :
        self.ma.Forward()
        self.mb.Forward()
        self.mc.Backward()
        self.md.Backward()
    def TurnRight(self) :
        self.ma.Backward()
        self.mb.Backward()
        self.mc.Forward()
        self.md.Forward()
    def Stop(self) :
        self.ma.Stop()
        self.mb.Stop()
        self.mc.Stop()
        self.md.Stop()

def main() :
    if len(sys.argv) != 2 :
        print sys.argv[0], " <cmd>"
        print " cmd 0   Forward"
        print "     1   Backward"
        print "     2   TurnLeft"
        print "     3   TurnRight"
        print "     4   Stop"
        sys.exit()

    mode = int(sys.argv[1])
    car = Car()
    if mode == 0 :
        car.Forward()
    elif mode == 1 :
        car.Backward()
    elif mode == 2 :
        car.TurnLeft()
        time.sleep(0.5)
        car.Stop()
    elif mode == 3 :
        car.TurnRight()
        time.sleep(0.5)
        car.Stop()
    elif mode == 4 :
        car.TurnLeft()
    elif mode == 5 :
        car.TurnRight()
    else :
        car.Stop()

if __name__ == "__main__" :
    main()
