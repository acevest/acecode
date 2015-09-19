#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: ant.py
#      Author: Zhao Yanbai
#              Sat Sep 19 14:08:56 2015
# Description: AceVest Net Tool
# ------------------------------------------------------------------------
import sys
import threading
import socket
import argparse
import select
import subprocess

gArgs = None

def DoRecv(s) :
    recvlen = 1
    response= ''
    while recvlen > 0 :
        data    = s.recv(4096)
        recvlen = len(data)
        response+= data

        #print('RECV {0}'.format(recvlen))

        if recvlen < 4096 :
            break

    return response

def ClientEntry() :
    global gArgs
    cs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try :
        cs.connect((gArgs.host, gArgs.port))
        cs.setblocking(True)

        while True :
            rs, _, _ = select.select([cs, sys.stdin], [], [])

            for fd in rs :
                if fd == sys.stdin :
                    data = fd.readline()
                    cs.send(data)
                elif fd == cs :
                    rsp = DoRecv(cs)
                    sys.stdout.write(rsp)
                    sys.stdout.flush()

    except Exception, e :
        print('[*] Exception! Exiting. {0}'.format(str(e)))

    cs.close()

def ExecuteCommand(cmd) :
    try :
        output = subprocess.check_output(cmd.strip(), stderr=subprocess.STDOUT, shell=True)
    except Exception, e:
        output = 'Failed to execute command. {0}\n'.format(str(e))
    return output

def ClientHandler(cs, ca) :
    global gArgs
    while True :
        if gArgs.shell :
            cs.send("<ANT#>")
        rs, _, _ = select.select([cs, sys.stdin], [], [])
        for fd in rs :
            if fd == sys.stdin :
                data = fd.readline()
                cs.send(data)
            elif fd == cs :
                req = DoRecv(cs)

                if gArgs.shell :
                    rsp = ExecuteCommand(req)
                    cs.send(rsp)

def ServerEntry() :
    global gArgs
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((gArgs.host, gArgs.port))
    s.listen(10)
    while True :
        cs, ca = s.accept()
        client_thread = threading.Thread(target=ClientHandler, args=(cs, ca, ))
        client_thread.start()

def ParseArguments() :
    global gArgs
    parser  = argparse.ArgumentParser(prog='ant', description='AceVest Network Tool')
    parser.add_argument('host',             help='hostname or host ip')
    parser.add_argument('port', type=int,   help='port')
    parser.add_argument('-l',   '--listen',     action='store_true', help='Bind and listen for incoming connections')
    parser.add_argument('-e',   '--execute',    action='store',      help='execute the command')
    parser.add_argument('-s',   '--shell',      action='store_true', help='initialize a shell')
    parser.add_argument('-u',   '--udp',        action='store_true', help='Use UDP instead of TCP')
    parser.add_argument('-t',   '--transfer',   action='store',      help='Transfer file')
    parser.add_argument('-v',   '--version',    action='version', version='%(prog)s 0.1')
    gArgs = parser.parse_args()


    #print(gArgs.listen)
    #print(gArgs.execute)

    if gArgs.listen :
        ServerEntry()
    else :
        ClientEntry()

def main() :
    ParseArguments()


if __name__ == "__main__" :
    main()
