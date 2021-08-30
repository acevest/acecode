#!/usr/bin/python3
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: aut.py
#      Author: Zhao Yanbai
#              2021-08-20 10:56:36 Friday CST
# Description: none
# ------------------------------------------------------------------------

import argparse
import socket
import sys


def UDPServer(addr) :
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(addr)
    while True :
        data = s.recv(1024)
        sys.stdout.write(data.decode(sys.stdout.encoding))
        sys.stdout.flush()



def main() :
    parser  = argparse.ArgumentParser(prog='aut', description='AceVest UDP Tool', epilog='')
    parser.add_argument('host',             help='hostname or host ip')
    parser.add_argument('port', type=int,   help='port')
    parser.add_argument('-l',   '--listen',     action='store_true', help='Bind and listen for incoming connections')
    parser.add_argument('-v',   '--version',    action='version', version='%(prog)s 0.2')
    arg = parser.parse_args()

    addr = (arg.host, arg.port)
    if arg.listen :
        UDPServer(addr)
    else :
        UDPClient(addr)


if __name__ == "__main__" :
    main()
