#!/usr/bin/env python
# ------------------------------------------------------------------------
#   File Name: directory.py
#      Author: Zhao Yanbai
#              Sun Feb 26 23:36:05 2012
# Description: none
# ------------------------------------------------------------------------
# -*- coding: utf-8 -*-

import os

pwd = "./"

def listFiles() :
    ret = {}
    for name in os.listdir(pwd) :
        path = os.path.join(pwd, name)
        if(os.path.isfile(path)) :
            ret[path] = os.path.getmtime(path)
    printRet(ret)

def walkDirs() :
    ret = {}
    for prefix, dirs, files in os.walk(pwd) :
        for name in files :
            path = os.path.join(prefix, name)
            ret[path] = 'file';
        for name in dirs :
            path = os.path.join(prefix, name)
            ret[path] = 'dirs';
    printRet(ret)

def printRet(ret) :
    for _ in ret.keys() :
        print "{1}:\t{0}".format(_, ret[_])


def main() :
    listFiles()
    print '-------------------------------------------'
    walkDirs()

main()
