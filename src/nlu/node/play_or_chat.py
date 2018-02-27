#!/usr/bin/env python
#-*- coding:utf-8 -*-
import sys
import rospy
from nlu.srv import *
from std_msgs.msg import String
from nlu.msg import IsPlayMusic
from KeyWordExtract import MusicInfo 
from ChatRobot import Tuling

#关键词解析
info = MusicInfo()
#聊天机器人
robot = Tuling()

pub = rospy.Publisher('nlu/robot_say', String, queue_size=10)

def callback(data):
    # rospy.loginfo(rospy.get_caller_id() + "[Partical Node] heard %s", data.isplay)
    if(data.isplay): #搜索数据库
        singer,song = info.getkey(data.topic)
     
    else:
        if(data.topic != 'Null'):
            msg = String()
            msg.data = robot.respon(data.topic)
            print msg.data
            pub.publish(msg)
       
      
def listener():
    rospy.init_node('partical', anonymous=True)
    rospy.Subscriber("nlu/isplay_music", IsPlayMusic, callback)
    rospy.spin()

if __name__ == '__main__':
    #初始化结巴分词模块，上传用户词条
    listener()