import web
import commands
from web.contrib.template import render_mako

urls = (
    '/',       'Page',
    '/Ctrl',    'Ctrl'
)

app = web.application(urls, globals())

render = web.template.render('./', cache = False)

class Page() :
    def GET(self) :
        return render.Page()

class Ctrl() :
    def GET(self) :
        action = int(web.input().get('action', 2))
        cmd = "python Car.py " + str(action)
        output = commands.getoutput(cmd)
        print output
        
if __name__ == "__main__" :
    app.run()
