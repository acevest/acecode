#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ------------------------------------------------------------------------
#   File Name: test.tcpsvr0.py
#      Author: Zhao Yanbai
#              Sat Sep 19 12:23:41 2015
# Description: none
# ------------------------------------------------------------------------

import socket
import threading

bindip  = "127.0.0.1"
bindport= 9999

# cs ---- client socket
# ca ---- client addr
def client_handler(cs, ca) :
    req = cs.recv(4096)
    print("[*] Recving data {0} from {1}:{2}".format(str(req), ca[0], ca[1]))
    cs.send(b"ACK\n");

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((bindip, bindport))
s.listen(5)
print("[*] Listening on {0}:{1}".format(bindip, bindport))

while True :
    cs, ca = s.accept()
    print("[*] Accepted connection from {0}:{1}".format(ca[0], ca[1]))

    client_handle_thread = threading.Thread(target=client_handler, args=(cs, ca))
    client_handle_thread.start()

