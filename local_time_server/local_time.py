#!/usr/bin/env python3

"""
This is a simple time server to display local time via http get request.
NTP internet servers only show UTC time and I want the local time for my custom made wall clock.
An alternative is to install a local NTP server, but running this python script is much simpler
both for setup and access.
"""

import time
from http.server import BaseHTTPRequestHandler, HTTPServer

WEB_PORT = 60000


class ResponseHandler(BaseHTTPRequestHandler):
    def _set_response(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

    def do_GET(self):
        self._set_response()
        local_time = time.localtime()
        self.wfile.write("{}:{}:{}".format(local_time.tm_hour, local_time.tm_min, local_time.tm_sec).encode('utf-8'))


def run():
    httpd = HTTPServer(('0.0.0.0', WEB_PORT), ResponseHandler)
    print('Starting local time server on port {}.'.format(WEB_PORT))

    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()

    print('Stopping local time server')


if __name__ == '__main__':
    run()
