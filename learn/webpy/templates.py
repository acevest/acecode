#!/usr/bin/env python
# ------------------------------------------------------------------------
#   File Name: templates.py
#      Author: Zhao Yanbai
#              Wed May  2 10:41:44 2012
# Description: none
# ------------------------------------------------------------------------
# -*- coding: utf-8 -*-

import web


urls = (
    '/Test', 'Test',
	'/(.*)', 'templates'
)

render = web.template.render("templates/")
app = web.application(urls, globals())

class FF :
    def __init__(self) :
        pass


def func() :
    return "so, it works"

class Test :
    def GET(self) :
        m = FF()
        m.x = 1
        m.y = 2

        rdr = web.template.render("templates/", globals={'dddd' : func })
        return rdr.Test(m)

class templates :
	def GET(self, name) :
		'''
			TemplateHTML means templates/TemplateHTML.html
			name means http://x.x.x.x:yyyy/name
			age means http://x.x.x.x:yyyy/name?age=123
		'''
		i = web.input(age=0)
		return render.TemplateHTML(name, i.age)


if __name__ == "__main__" :
	app.run()
