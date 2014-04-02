#!/usr/bin/env python
# -*- coding: utf-8 -*-
# --------------------------------------------------------------------------
#   File Name:	analyzeCSDN.py
#      Author:	Zhao Yanbai
#		Fri Jan 13 12:17:10 2012
# Description:	将网络上泄露的CSDN网站的账号密码及电子邮件信息提取出来并构造
#               成插入数据库的SQL语句
# --------------------------------------------------------------------------

import re

try :
    inf = open("./www.csdn.net.sql", "r")
    ouf = open("./csdn.sql", "w")
except IOError as ioerr :
    print "Error: ", ioerr
    exit();

# 将每10000条记录生成成一条SQL
# 如果一条SQL中含的记录太多，则在MYSQL中执行会超时
itemperline = 10000

i = 0
while True:

    line = inf.readline()

    if(len(line) == 0) :
        ouf.write(";")
        break;

    # 去掉行尾的 \r\n
    line = line[:-2]

    # 将gb2312编码转换成utf-8编码
    try :
        line = unicode(line, "gbk").encode("utf-8")
    except UnicodeDecodeError as err :
        print "Error Msg: ", err
        print "Error Line: ", line
        continue

    # 构造的SQL语句针对客串形式的参数需要用至"'"
    # 所以需要将密码中的"'"转换成"\'"，涉及到转义的问题，所以为"\\'"
    # 如果\是最后一个字符也会造成SQL语句构造错误
    line = line.replace("\\", "\\\\")
    line = line.replace("'", "\\'")

    # 提取用户名、密码、Email
    D = re.findall(r'(.*) # (.*) # (.*)', line)

    # 构造SQL语句
    if(i % itemperline == 0) :
        ouf.write("INSERT INTO csdn VALUES")
    else :
        ouf.write(",")
    ouf.write("(NULL,'" + D[0][0] +"','" + D[0][1] +"','" + D[0][2] + "')")
    if((i+1) % itemperline == 0) :
        ouf.write(";")

    i += 1

inf.close();
ouf.close();
