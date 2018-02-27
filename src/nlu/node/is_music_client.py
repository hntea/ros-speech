#!/usr/bin/env python
#-*- coding:utf-8 -*-
import sys
import rospy
from nlu.srv import *
from std_msgs.msg import String
import jieba 
import jieba.posseg as pseg
from nlu.msg import IsPlayMusic

#消息发布
pub = rospy.Publisher('nlu/isplay_music', IsPlayMusic, queue_size=10)

#请求服务
def is_music_clint(topic):
    rospy.wait_for_service('is_music')  #绑定服务
    try:
        is_music = rospy.ServiceProxy('is_music', IsMusic)   #获取回话语句柄
        resp1 = is_music(topic)         #发送请求
        return resp1.ismusic
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e



#服务器响应回调函数
def callback(data):
    #rospy.loginfo(rospy.get_caller_id() + "  I heard %s", data.data)
    ret = is_music_clint(data.data) 
    msg = IsPlayMusic()
    msg.topic = data.data
    if ret == 1:
        msg.isplay = 1
        print "-------------音乐走起-----------"
        pub.publish(msg)
    else:
        msg.isplay = 0
        if(data.data != 'Null'):
            print ">>>>>>机器人："
        pub.publish(msg)

def is_music():
    rospy.init_node('nlu_is_music_client', anonymous=True)
    rospy.Subscriber("asr/xf/b_res", String, callback)
    rospy.spin()

if __name__ == "__main__":
    '''
    节点说明：
    对识别结果进行是否在本地播放音乐的预判
    '''
    #初始化客户节点
    is_music()