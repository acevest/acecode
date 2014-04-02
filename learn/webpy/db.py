#!/usr/bin/env python
# ------------------------------------------------------------------------
#   File Name: db.py
#      Author: Zhao Yanbai
#              Wed May  2 11:32:00 2012
# Description: none
# ------------------------------------------------------------------------
# -*- coding: utf-8 -*-

import web

urls = (
	'/dbList', 'database'
)

app = web.application(urls, globals())
render = web.template.render("templates/")
db = web.database(dbn='mysql', user='webpy', pw='webpy', db='webpy')
# host='localhost', port=3306, charset='utf8')

class database :
	def GET(self) :
		users = db.select('user')
		return render.dbList(users)


if __name__ == "__main__" :
	app.run()
