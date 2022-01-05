#!/usr/bin/env python3

from flask import Flask, request, render_template, Markup, send_from_directory, g, redirect, make_response
import time


application = Flask(__name__)
WEB_PORT = 60000


@application.route('/')
def home_page():
    local_time = time.localtime()
    return "{}:{}:{}".format(local_time.tm_hour, local_time.tm_min, local_time.tm_sec)


if __name__ == '__main__':
    application.run(host="0.0.0.0", port=WEB_PORT, debug=True)
