#!/usr/bin/env python
#-*- coding:utf-8 -*-
import sys
import rospy
import os
from std_msgs.msg import String
from BDTTS import BaiduTTS
from FileManager import FileManager
reload(sys)
sys.setdefaultencoding( "utf-8" )
#消息发布
pub = rospy.Publisher('tts/mp3', String, queue_size=10)

#合成器
bd_tts = BaiduTTS()
#文件管理
fm = FileManager()



def callback(data):
    print "正在合成..."
    text = data.data
    savefile = fm.allocfile('/home/hntea/ros-speech/baidu/tts/','tts')
    bd_tts.run(text,savefile)
    msg = String()
    msg.data = savefile
    pub.publish(msg)

def tts():
    rospy.init_node('bds_tts', anonymous=True)
    rospy.Subscriber("nlu/robot_say", String, callback)
    rospy.spin()

if __name__ == "__main__":
    '''
    节点说明：
    百度语音合成
    '''
    #初始化客户节点
    tts()