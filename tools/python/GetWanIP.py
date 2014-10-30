#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: GetWanIP.py
#      Author: Zhao Yanbai
#              Thu Oct 30 04:34:37 2014
# Description: none
# ------------------------------------------------------------------------
import os
import re,urllib2
import smtplib  
import ConfigParser
import config
from email.mime.text import MIMEText  
from utils import * 

'''
    CONFIG FILE SAMPLE
[EMAIL]
MAILTO  = xxx@xx.com
MAILHOST= smtp.xx.com
MAILUSER= xxxxx
USERNICK= xxx
MAILPASS= *****
MAILPOSTFIX= xx.com
'''
'''
    CONTAB
* * * * * root cd /xxx/xxx/xxx/ && python GetWanIP.py
'''

TMP_FILE_PATH = '/tmp/GetWanIP.txt'
log = CreateLogger(config.ACE_GLOBAL_LOG_PATH)
  
mailto_list=[] 
mail_host=""        #设置服务器
mail_user=""        #用户名
user_nick=""
mail_pass=""        #口令 
mail_postfix=""     #发件箱的后缀

class GetWanIP:
    def GetIP(self):
        try:
            log.info('Try ip.qq.com')
            WanIP = self.Visit('http://ip.qq.com')
        except:
            s = 'Failed to Get WanIP!!!'
            WanIP = s
            log.error(s)
        return WanIP

    def Visit(self,url):
        opener = urllib2.urlopen(url)
        if url == opener.geturl():
            str = opener.read()
        return re.search('\d+\.\d+\.\d+\.\d+',str).group(0)


def send_mail(to_list,sub,content):                                 #to_list：收件人；sub：主题；content：邮件内容
    me=user_nick+"<"+mail_user+"@"+mail_postfix+">"                 #这里的hello可以任意设置，收到信后，将按照设置显示
    msg = MIMEText(content,_subtype='html',_charset='gb2312')       #创建一个实例，这里设置为html格式邮件
    msg['Subject'] = sub                #设置主题
    msg['From'] = me  
    msg['To'] = ";".join(to_list)  
    try:  
        s = smtplib.SMTP()  
        s.connect(mail_host)                        #连接smtp服务器
        s.login(mail_user,mail_pass)                #登陆服务器
        s.sendmail(me, to_list, msg.as_string())    #发送邮件
        s.close()  
        return True  
    except Exception, e:  
        log.error(str(e))
        return False  
if __name__ == '__main__':  
    try :
        fd = open(TMP_FILE_PATH)
        OldWanIP = fd.readline().strip()
        fd.close()
    except :
        OldWanIP = '0.0.0.0'

    getWanIP = GetWanIP()
    WanIP = getWanIP.GetIP()

    cnfp = ConfigParser.ConfigParser()
    cnfp.read(config.ACE_GLOBAL_CONF_PATH)
    mailto_list.append(cnfp.get('EMAIL', 'MAILTO'))
    mail_host = cnfp.get('EMAIL', 'MAILHOST')
    mail_user = cnfp.get('EMAIL', 'MAILUSER')
    user_nick = cnfp.get('EMAIL', 'USERNICK')
    mail_pass = cnfp.get('EMAIL', 'MAILPASS')
    mail_postfix = cnfp.get('EMAIL', 'MAILPOSTFIX')

    if OldWanIP != WanIP :
        s = 'WanIP has Changed From ' + OldWanIP + ' To ' + WanIP
        log.info(s)
        if send_mail(mailto_list,u'外网IP有变动', s):  
            log.info('发送成功')
            fd = open(TMP_FILE_PATH, 'w+')
            fd.write(WanIP+'\n')
            fd.close()
        else:  
            log.error('发送失败')
