#!/usr/bin/env python3

"""
This is the same as the local_time.py except it does not send the local time, 
but custom time so I can test the mechanics of the clock.
"""

import time
import socket

WEB_PORT = 60000

s = 0
m = 0
h = 0

total_seconds = h * 3600 + m * 60 + s
message = "{}".format(total_seconds).encode('utf-8')

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
server.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

# UDP is not guaranteed to arrive so broadcast few times
server.sendto(message, ("192.168.0.255", WEB_PORT))
time.sleep(0.1)
server.sendto(message, ("192.168.0.255", WEB_PORT))

print("Sent: {}".format(message), flush=True)

server.close()
