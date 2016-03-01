#!/usr/bin/env python3

import json
from os.path import dirname, join

import tornado.web
from tornado.ioloop import IOLoop
from tornado.options import define, options, parse_command_line

from networktables import NetworkTable
from pynetworktables2js import get_handlers, NonCachingStaticFileHandler

#import logging
#logger = logging.getLogger('dashboard')

# Setup logging
#log_datefmt = "%H:%M:%S"
#log_format = "%(asctime)s:%(msecs)03d %(levelname)-8s: %(name)-20s: %(message)s"

#logging.basicConfig(datefmt=log_datefmt,
#                   format=log_format,
#                   level=logging.DEBUG)

class ConfigHandler(tornado.web.RequestHandler):
    '''Writes JSON that the HTML page can retrieve'''
    
    def get(self):
        self.write('var Config = ' + json.dumps({
            'webcam': options.webcam
        }) + ';')
        


def init_networktables(ipaddr):

    #logger.info("Connecting to networktables at %s" % ipaddr)
    NetworkTable.setIPAddress(ipaddr)
    NetworkTable.setClientMode()
    NetworkTable.initialize()
    #logger.info("Networktables Initialized")


def main():
<<<<<<< HEAD:src/SmartDashboard/initialize.py
    define("webcam", default="http://raspberrypi.local:8080/?action=stream", help="URL for the webcam", type=str)
    define("host", default='roborio-3322-frc.local', help="Hostname of robot", type=str)
=======
    define("webcam", default="http://10.14.18.2:1180", help="URL for the webcam", type=str)
    define("host", default='127.0.0.1', help="Hostname of robot", type=str)
>>>>>>> 2e1ed47fea37d246ae26df3cfae5b07997a9a29e:src/SmartDashboard/initialize.py
    define("port", default=3322, help="run on the given port", type=int)

    parse_command_line()
    
    

    init_networktables(options.host)
    
    app = tornado.web.Application(
        get_handlers() + [
            (r"/config.js", ConfigHandler),
            (r"/()", NonCachingStaticFileHandler, {"path": join(dirname(__file__), 'UI_MainPage.html')}),
            (r"/(.*)", NonCachingStaticFileHandler, {"path": dirname(__file__)}),
        ]
    )
    
    #logger.info("Listening on http://localhost:%s/" % options.port)

    app.listen(options.port)
    IOLoop.instance().start()


if __name__ == '__main__':
    main()
