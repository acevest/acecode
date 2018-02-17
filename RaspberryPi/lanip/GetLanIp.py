#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: GetLanIp.py
#      Author: Zhao Yanbai
#              2016-07-04 23:14:50 Monday CST
# Description: none
# ------------------------------------------------------------------------
import socket
import fcntl
import struct
import os
import sys
import time
import re,urllib2
import smtplib
import ConfigParser
from email.mime.text import MIMEText
from email.header import Header

def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', ifname[:15])
    )[20:24])

def SendMail(title, content) :
    cnfp = ConfigParser.ConfigParser()

    cnfp.read(os.path.split(os.path.realpath(__file__))[0]+'/mail.conf')

    mail_host = cnfp.get('EMAIL', 'MAILHOST')  # 服务器
    mail_user = cnfp.get('EMAIL', 'MAILUSER')  # 用户名
    mail_pass = cnfp.get('EMAIL', 'MAILPASS')  # 口令
    sender    = cnfp.get('EMAIL', 'SENDER')    # 发送方
    receivers = [cnfp.get('EMAIL', 'MAILTO')]  # 接收邮件，可设置为你的QQ邮箱或者其他邮箱

    message = MIMEText(content, 'plain', 'utf-8')

    subject = title + '[' + cnfp.get('EMAIL', 'DEVICE') + ']'
    message['Subject'] = Header(subject, 'utf-8')


    try:
        smtpObj = smtplib.SMTP_SSL()
        smtpObj.connect(mail_host, 465)
        smtpObj.login(mail_user,mail_pass)
        smtpObj.sendmail(sender, receivers, message.as_string())
        print "邮件发送成功"
    except smtplib.SMTPException, e:
        print e
        print "Error: 无法发送邮件"


if __name__ == "__main__" :
    while True :
        lanip = { 'wlan0':'NULL', 'eth0':'NULL', 'lo':'NULL' }
        for k, v in lanip.items() :
            try :
                lanip[k] = get_ip_address(k)
            except :
                continue

        if lanip['wlan0'] == 'NULL' :
            time.sleep(1)
            continue

        try :
            SendMail("LanIp", str(lanip))
            break
        except:
            time.sleep(1);
            continue

