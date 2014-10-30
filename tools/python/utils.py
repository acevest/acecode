#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: utils.py
#      Author: Zhao Yanbai
#              Thu Oct 30 06:33:24 2014
# Description: none
# ------------------------------------------------------------------------

import logging

def CreateLogger(logpath, level=logging.DEBUG)  :
    logger  = logging.getLogger(logpath)
    fmtr    = logging.Formatter('%(levelname)s\t%(asctime)s: %(message)s')

    fileHdlr    = logging.FileHandler(logpath)
    fileHdlr.setFormatter(fmtr)
    fileHdlr.setLevel(level)

    streamHdlr  = logging.StreamHandler()
    streamHdlr.setFormatter(fmtr)
    streamHdlr.setLevel(level)

    logger.addHandler(fileHdlr)
    logger.addHandler(streamHdlr)
    logger.setLevel(level)

    return logger

