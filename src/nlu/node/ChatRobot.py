#!/usr/bin/env python
#-*- coding:utf-8 -*-
# TulingNLUClientManager.py
# Created on: 2017年1月5日
#    Author: hntea
import os
import urllib2
import json as js


class Tuling:
    def __init__(self):
        self.__readconfig(self.__defaultconfig())

    def __defaultconfig(self):
          config = os.path.join(os.environ["HOME"],"ros-speech/config/config.json")
          return config
              
    def __readconfig(self,file):
        with open(file) as fd:
            jsout = js.load(fd)
            server = jsout["speechServer"]["tuling"]["server"]
            apikey = jsout["speechServer"]["tuling"]["apikey"]
        fd.close()
        self.__server = server.encode("utf-8")
        self.__apikey = apikey.encode("utf-8")

    
    def respon(self,topic):
        url = self.__server+"?key=" + self.__apikey +"&info=" + topic
        f = urllib2.urlopen(url)
        txt = js.loads(f.read())['text']
        return txt




