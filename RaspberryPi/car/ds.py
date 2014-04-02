#!/bin/env python
# -*- coding:utf-8 -*-
# -------------------------------
# Revision:
# Date:        2012-12-11
# Author:      simonzhang
# Email:       simon-zzm@163.com
# Web:         www.simonzhang.net
# ------------------------------- 
import time
import commands
import RPi.GPIO as GPIO
import datetime as dt
 
# 初始化
# 需要注意输出与输入的接口
# 8为发射，10为接收
#GPIO.setmode(GPIO.BCM)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(8, GPIO.OUT)
GPIO.setup(10, GPIO.IN)

delta = 0
LstDs = 0
while  1:
    time.sleep(0.01)
    # IO 触发，给10us的高电平
    # 模块自动发送8个40khz的方波
    GPIO.output(8, GPIO.HIGH)
    time.sleep(0.00001)
    GPIO.output(8, GPIO.LOW)
    # 获取发射完毕时间
    # 未接收为False，循环检查开始接受点
    # 转为True为开始接受
    tb = time.time()
    while GPIO.input(10) == False:
       if time.time() - tb > 1 :
            break
       pass
    t1 = time.time()
    # 循环检查开始接收，转为False。则为接受完毕
    tb = time.time()
    while GPIO.input(10):
       if time.time() - tb > 1 :
            break
       pass
    # 获取接受完毕时间
    t2 = time.time()
    # 计算发送与接收时间差
    t3 = t2-t1
    # 空气中1个标准大气压在温度15度时速度为340m/s
    # 25度为346m/s
    # 所以按照一秒钟34000厘米计算
    # 根据硬件文档，该模块探测距离在2-400cm之间
    # 测试范围的时间间隔应该为0.00010到0.023529
    # 为了方便取值自行变化一点
    ds = 340 * t3 / 2
    print "{0}\t{1:.2f}".format(time.time(), ds)
    if ds < 0.3 and LstDs - ds < 0:
        cmd = "python Car.py 6"
        print cmd
        commands.getoutput(cmd)

    LstDs = ds

