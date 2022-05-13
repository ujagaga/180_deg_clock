#!/usr/bin/env python3

"""
This is a simple time server to broadcast local time (number of seconds passed today) via UDP.
NTP internet servers only show UTC time and I want the local time for my custom made wall clock.
An alternative is to install a local NTP server or add NTP feature in the wall clock firmware,
which makes daylight savings complicated. Running this python script is much simpler.
Place this scipt to run at system startup.
"""

import time
import socket

WEB_PORT = 60000

local_time = time.localtime()
total_seconds = local_time.tm_hour * 3600 + local_time.tm_min * 60 + local_time.tm_sec
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
