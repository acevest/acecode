#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: ant.py
#      Author: Zhao Yanbai
#              Sat Sep 19 14:08:56 2015
# Description: AceVest Net Tool
# ------------------------------------------------------------------------
import os
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
        #cs.setblocking(False)

        while True :
            rs, _, es = select.select([cs, sys.stdin], [], [cs])

            for fd in rs :
                if fd == sys.stdin :
                    data = fd.readline()
                    if len(data) == 0 :
                        cs.close()
                        return
                    cs.send(data)
                elif fd == cs :
                    rsp = DoRecv(cs)
                    if len(rsp) == 0 :
                        cs.close()
                        return
                    sys.stdout.write(rsp)
                    sys.stdout.flush()

    except Exception, e :
        print('[*] Exception! Exiting. {0}'.format(str(e)))

def ExecuteCommand(cmd) :
    try :
        cmd = cmd.strip()
        print('[*] Execute Command: {0}'.format(cmd))
        output = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True)
    except Exception, e:
        output = 'Failed to execute command. {0}\n'.format(str(e))
    return output

def ClientHandler(cs, ca) :
    global gArgs

    if len(gArgs.execute) != 0 :
        print('[!] Executing {0} for {1}:{2}'.format(gArgs.execute, ca[0], ca[1]))
        if os.fork() == 0 :
            os.dup2(cs.fileno(), sys.stdin.fileno())
            os.dup2(cs.fileno(), sys.stdout.fileno())
            os.dup2(cs.fileno(), sys.stderr.fileno())
            cs.send('Executing {0} for you {1}:{2}\n'.format(gArgs.execute, ca[0], ca[1]))
            os.system(gArgs.execute)
            cs.send('Bye...\n')
            sys.exit()
        else :
            cs.close()
            return

    while True :
        if gArgs.shell :
            cs.send("<ANT#>")
        rs, _, es = select.select([cs, sys.stdin], [], [])
        for fd in rs :
            if fd == sys.stdin :
                data = fd.readline()
                cs.send(data)
            elif fd == cs :
                req = DoRecv(cs)
                if len(req) == 0 :
                    cs.close()
                    print('[!] Client {0}:{1} Exit.'.format(ca[0], ca[1]))
                    return
                    
                if gArgs.shell :
                    if req.strip() != 'exit' :
                        rsp = ExecuteCommand(req)
                        cs.send(rsp)
                    else :
                        cs.send('Exiting...\n')
                        cs.close()
                        return
                else :
                    sys.stdout.write(req)
                    sys.stdout.flush()


def ServerEntry() :
    global gArgs
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
    s.bind((gArgs.host, gArgs.port))
    s.listen(10)
    s.setblocking(True)
    while True :
        cs, ca = s.accept()
        print('[*] Accept connection from {0}:{1}'.format(ca[0], ca[1]))


        client_thread = threading.Thread(target=ClientHandler, args=(cs, ca, ))
        client_thread.start()

def ParseArguments() :
    global gArgs
    parser  = argparse.ArgumentParser(prog='ant', description='AceVest Network Tool', epilog='')
    parser.add_argument('host',             help='hostname or host ip')
    parser.add_argument('port', type=int,   help='port')
    parser.add_argument('-l',   '--listen',     action='store_true', help='Bind and listen for incoming connections')
    parser.add_argument('-e',   '--execute',    action='store',      help='execute the command')
    parser.add_argument('-s',   '--shell',      action='store_true', help='a simple shell. enter exit to exit.')
    parser.add_argument('-u',   '--udp',        action='store_true', help='Use UDP instead of TCP')
    parser.add_argument('-t',   '--transfer',   action='store',      help='Transfer file')
    parser.add_argument('-v',   '--version',    action='version', version='%(prog)s 0.1')
    gArgs = parser.parse_args()


    if gArgs.shell and gArgs.execute != '' :
        print "parameter error: -s or -e"
        sys.exit()

    if gArgs.listen :
        ServerEntry()
    else :
        ClientEntry()

def main() :
    ParseArguments()


if __name__ == "__main__" :
    main()
