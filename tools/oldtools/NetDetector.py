#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: NetDetector.py
#      Author: AceZhao
#              Copyright (C) 2013 GZRD,Tencent. All Rights Reserved.
#              Fri Mar 29 11:09:56 2013
# Description: none
# ------------------------------------------------------------------------
import os
import sys
import socket
import logging
import time
from threading import Timer

gPort       = 0xACE
gSndPktCnt  = 0xACE
gSndDst     = ''
gPktSize    = 100
gSndHz      = 100
gSndDelay   = 1


logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s %(message)s',
                    filename='log.{0}.txt'.format(time.strftime('%Y%m%d%H%M%S', time.localtime(time.time()))),
                    filemode='w+')

class Storage(dict) :
    def __getattr__(self, key) :
        try :
            return self[key]
        except KeyError, k:
            raise AttributeError, k

    def __setattr__(self, key, value) :
        self[key] = value

    def __delattr__(self, key) :
        try :
            del self[key]
        except KeyError, k:
            raise AttributeError, k

    def __repr__(self) :
        return '<Storage ' + dict.__repr__(self) + '>'


class Data(Storage) :
    def __init__(self) :
        self.Sn = 0
        self.size = 0
        self.Data = '0'

    def Init(self, sn, size) :
        self.Sn = sn
        self.Size = size

        msg = ""
        for i in range(0, size-len(str(self.Sn))) :
            msg += ' '

        self.Data = str(self.Sn) + msg

    def InitWithMsg(self, msg) :
        self.Sn = msg.strip()
        self.Size = len(msg) - len(self.Sn)
        self.Data = msg

    def GetData(self) :
        return self.Data


def Log(s) :
    logging.error(s)


gSndSn = 0
def SndPkts() :
        global gSndSn,gSndDelay,gSndPktCnt
        data = Data()
        data.Init(gSndSn, gPktSize)
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	s.bind(('', 2766))
        s.sendto(data.GetData(), (gSndDst, gPort))
        Log('sended sn {0}'.format(data.Sn))
        gSndSn += 1
        if gSndSn < gSndPktCnt :
            Timer(gSndDelay, SndPkts, ()).start()
	s.close()

def Client() :
    global gSndDelay, gSndSn, gSndPktCnt
    gSndSn = 0
    print gSndDelay
    Timer(gSndDelay, SndPkts, ()).start()
    Log('send data size {0}'.format(gPktSize))
    while True :
        print gSndSn, gSndPktCnt
        if gSndSn >= gSndPktCnt :
            break
        time.sleep(1)

def Server() :
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(('',gPort))
    Log('waiting on port {0}'.format(gPort))
    while True :
        (msg, (addr, port)) = s.recvfrom(1024)
        data  = Data()
        data.InitWithMsg(msg)
	print "dsfasdfads"
        Log('received sn {0}'.format(data.Sn))

def main() :
    mode = 'cli'
    try :
        mode = sys.argv[1]
    except :
        print "svr or cli ?"
        sys.exit()
    global gSndDst, gPort, gSndPktSize, gSndPktCnt, gSndHz, gSndDelay

    if mode == 'cli' :
        if len(sys.argv) != 7 :
            print "{0} <cli> <SndDst> <Port> <SndPktSize> <SndPktCnt> <SndHz>".format(sys.argv[0])
            sys.exit()

        gSndDst = sys.argv[2]
        gPort = int(sys.argv[3])
        gSndPktSize = int(sys.argv[4])
	gSndPktCnt = int(sys.argv[5])
        gSndHz = int(sys.argv[6])
        gSndDelay = float(1.0 / (gSndHz+gSndHz*0.01))
        Client()
    elif mode == 'svr' :
        if len(sys.argv) != 3 :
            print "{0} <svr> <Port>".format(sys.argv[0])
            sys.exit()
        gPort = int(sys.argv[2])
        Server()
    else :
        pass

if __name__ == "__main__" :
    main()
