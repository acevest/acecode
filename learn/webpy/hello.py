#!/usr/bin/env python
# ------------------------------------------------------------------------
#   File Name: hello.py
#      Author: Zhao Yanbai
#              Wed May  2 09:44:56 2012
# Description: none
# ------------------------------------------------------------------------
# -*- coding: utf-8 -*-
import web 

urls = (
	'/.*', 'index'
)


class index:
	def GET(self) :
		return "Hello, World"

if __name__ == "__main__" :
	app = web.application(urls, globals())
	app.run()

