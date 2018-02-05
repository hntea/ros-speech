#-*- coding:utf-8 -*-
import sys
import rospy
from tgrocery import Grocery
from nlu.srv import *

model = '/home/hntea/ros-speech/nlu-model/sample'
new_grocery = Grocery(model)

def handle_is_music(req):
    print "Request = [%s]"%(req.topic)
    label =  str(new_grocery.predict(req.topic))
    if label=='music':
        ret = 1
    else:
        ret = 0    
    return ret

def is_music_server():
    rospy.init_node('nlu_is_music')
    s = rospy.Service('is_music', IsMusic, handle_is_music)
    print "Servic Is Ready"
    rospy.spin()

if __name__ == "__main__":
    print "Servic Load Model..."
    new_grocery.load()              # 加载模型

    is_music_server()