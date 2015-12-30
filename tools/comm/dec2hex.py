#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: dec2hex.py
#      Author: Zhao Yanbai
#              Tue Apr 28 15:00:56 2015
# Description: none
# ------------------------------------------------------------------------
import sys

def main() :
    while True :
        n = 0
        inputdata = raw_input("> ")
        if inputdata.lower() == 'quit' :
            sys.exit()

        try :
            n = int(inputdata)
        except ValueError,e :
            print "ERROR: ", e
            continue

        hexs = "{0:X} 0x{1:X}".format(n, n)
        print hexs


if __name__ == "__main__" :
    try :
        main()
    except KeyboardInterrupt :
        print "Bye..."
        pass
