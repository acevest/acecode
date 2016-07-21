#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: asm2scs.py
#      Author: Zhao Yanbai
#              2016-07-21 22:08:07 Thursday CST
# Description: asm to shellcode string
# ------------------------------------------------------------------------

import os
import sys
import argparse
import commands
import re

gArgs = None


def isValidAddr(addr) :
    for c in addr :
        if c not in set(['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']) :
            return False


    return True

def getShellCode(asmpath) :
    sc = ''
    try :
        cmd = 'nasm -f macho {0} -o {0}.o;otool -tjV {0}.o'.format(asmpath)
        print cmd
        output = commands.getoutput(cmd)
        lines = [line.strip() for line in output.splitlines()]
        for line in lines :
            d = line.split('\t')
            if len(d) < 3 or not isValidAddr(d[0]):
                continue

            sc += d[1].strip().upper()

    except Exception, e:
        print("Exception: {0}".format(e))

    return sc


def formatShellCode(sc) :
    fsc = ''
    if len(sc) % 2 != 0 :
        print("Invalid ShellCode")
    else :
        while sc != '' :
            fsc += '\\x' + sc[:2]
            sc = sc[2:]

    print fsc
    return fsc

def parseArguments() :
    global gArgs
    parser = argparse.ArgumentParser(prog='asm2scs', description='asm to shellcode string', epilog='')
    parser.add_argument('-a', '--asm',      action='store',     default='',     help='asm file path')
    parser.add_argument('-v', '--version',  action='version',   version='%(prog)s 0.1')
    gArgs = parser.parse_args()


    if not gArgs.asm or gArgs.asm == '' :
        print("invalid asm file path")
        return False

    return True

def main() :
    if not parseArguments() :
        return False


    sc = getShellCode(gArgs.asm)
    formatShellCode(sc)


if __name__ == "__main__" :
    main()
