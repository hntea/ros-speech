#!/usr/bin/env python
#-*- coding:utf-8 -*-
import sys
import os


class FileManager:

    def __init__(self):
        self.fid = 0
        pass
    
    def allocfile(self,wkdir,file,num=10):
        '''
        分配文件名：
        '''
        if not os.path.exists(wkdir):
            os.makedirs(wkdir)
        if(self.fid >= num):
            self.fid = 0
        name = wkdir+file+str(self.fid)+".mp3"
        self.fid += 1
        return name    

if __name__ == '__main__':
    manager = FileManager()
    print manager.allocfile("/home/hntea/ros-speech/baidu/test/",'tts')
    for x in range(0,10):
        print manager.allocfile("/home/hntea/ros-speech/baidu/tts/",'tts')