#!/usr/bin/env python
# ------------------------------------------------------------------------
#   File Name: OptParse.py
#      Author: Zhao Yanbai
#              Sun Feb 26 00:41:55 2012
# Description: none
# ------------------------------------------------------------------------
# -*- coding: utf-8 -*-

# python已经不再更新本库,可以改用argparse

import optparse
def main() :
    parser = optparse.OptionParser()
    parser.add_option("-w", "--maxwidth", dest="maxwidth", type="int",
                    help= "the maximum number of characters that can " +\
                          "be output to string fields [default:%default]")
    parser.add_option("-f", "--format", dest="format",
                    help="the format used for outputting numbers " +\
                         "[default:%default]")

    parser.set_defaults(maxwidth=100, format=".0f")
    opts, args = parser.parse_args()

main()

