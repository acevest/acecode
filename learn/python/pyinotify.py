#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: pyinotify.py
#      Author: Zhao Yanbai
#              Thu Oct 30 05:56:56 2014
# Description: none
# ------------------------------------------------------------------------

from pyinotify import WatchManager, Notifier, ProcessEvent, EventsCodes

class EventHandler(ProcessEvent) :
    def process_IN_MODIFY(self, event) :
        print("Modify file: ", event.path)


def Monitor(path) :
    wm = WatchManager()
    mask = EventsCodes.FLAG_COLLECTIONS['OP_FLAGS']['IN_MODIFY']
    print "mask ", mask
    

    notifier = Notifier(wm, EventHandler())
    wm.add_watch(path, mask, rec=True)
    print 'Now Start to Watching ', path
    while True :
        try :
            notifier.process_events()
            if notifier.check_events() :
                notifier.read_events()

        except KeyboardInterrupt :
            notifier.stop()
            break 


if __name__ == "__main__" :
    Monitor('./a.txt')





