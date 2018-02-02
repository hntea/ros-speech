# -*- coding:utf-8 -*-

import array
import os
from matplotlib import pyplot

file1 = '/home/hntea/ros-speech/audio/无前后向缓存.pcm'
file2 = '/home/hntea/ros-speech/audio/有前后向缓存.pcm'

def loadfile(file):
    base = 1/(1<<15)
    fd = open(file,'rb')
    arr = array.array('h') # int16
    size = int(os.path.getsize(file)/arr.itemsize)
    arr.fromfile(fd,size)
    fd.close()
    return arr


def show(data1,data2,start,end1,end2):
    fig = pyplot.figure(1)
    pyplot.subplot(211)
    pyplot.title('No PreBackFrames Algorithm')
    pyplot.plot(range(start, end1), data1[start:end1])
    pyplot.subplot(212)
    pyplot.title('Add PreBackFrames Algorithm')
    pyplot.plot(range(start, end2), data2[start:end2])
    pyplot.show()

def showfull(data,start,end):
     fig = pyplot.figure(1)
     pyplot.subplot(111)
     pyplot.title("Add PreBack Algorithm")
     pyplot.plot(range(start, end), data[start:end])
     pyplot.show()

arr1 = loadfile(file1)
len1 = len(arr1)
arr2 = loadfile(file2)
len2 = len(arr2)
show(arr1,arr2,0,len1,len2)
