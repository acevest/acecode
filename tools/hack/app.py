#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: app.py
#      Author: Zhao Yanbai
#              Tue Sep 29 10:27:23 2015
# Description: AceVest Packet Peeper
# ------------------------------------------------------------------------

import os
import sys
import argparse
import scapy.all
import netaddr
import re
import urllib
import urllib2
import BaseHTTPServer

gArgs = None

def ParseArguments() :
    global gArgs
    parser  = argparse.ArgumentParser(prog='app', description='AceVest Packet Peeper', epilog='')
    parser.add_argument('-i',   '--iface',      action='store',     default='any',  help='peeper interface')
    parser.add_argument('-f',   '--filter',     action='store',     default='',     help='filter string')
    parser.add_argument('-c',   '--count',      action='store',     default='0',    help='peeper packet count')
    parser.add_argument('-v',   '--version',    action='version',   version='%(prog)s 0.1')
    gArgs = parser.parse_args()


class HTTPRequest(BaseHTTPServer.BaseHTTPRequestHandler) :
    def __init__(self, request) :
        self.raw_requestline = request
        self.parse_request()


def DoHttpHeader(s, port) :
    lines = s.split('\r\n')
    path = None
    host = None

    for l in lines :
        if l[:4] == 'GET ' :
            path = l.split()[1]
        if l[:5] == 'Host:' :
            host = l.split()[1]

    print host+':'+str(port)+urllib.unquote_plus(path)

def DoHttp(s, port) :
    '''
    print s
    print '-'*80
    print urllib2.parse_keqv_list(s)
    print '-'*80
    hr = HTTPRequest(s)
    print hr
    h = BaseHTTPServer.BaseHTTPRequestHandler()
    h.raw_requestline = s
    h.parse_request()
    return
    '''
    if s[:4] == 'GET ' or s[:5] == 'POST ' :
        DoHttpHeader(s, port)

def PacketCallback(packet) :
    #print packet.show()
    if packet['IP'].proto == scapy.all.IP_PROTOS.tcp:
        if packet['TCP'].dport in [80, 8080] :
            DoHttp(str(packet['TCP'].payload), packet['TCP'].dport)

def DoPeeper() :
    global gArgs
    '''
    print gArgs.iface
    print gArgs.filter
    print gArgs.count

    for ip in netaddr.IPNetwork('192.168.1.1/30') :
        print ip
    '''

    scapy.all.sniff(filter=gArgs.filter, iface=gArgs.iface, prn=PacketCallback, count=gArgs.count, store=0)


def main() :
    try :
        ParseArguments()
        DoPeeper()
    except KeyboardInterrupt, e:
        Print("\n[!] User force to quit.")


if __name__ == "__main__" :
    main()
