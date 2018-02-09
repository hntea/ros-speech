#!/usr/bin/env python
#-*- coding:utf-8 -*-
import sys
import rospy
from nlu.srv import *
from std_msgs.msg import String
import jieba 
import jieba.posseg as pseg
from nlu.msg import IsPlayMusic


class Partical(object):
    '''
    对结巴分词工具在封装，主要提取输入语句的歌手和歌名
    '''
    def __init__(self):
        pass
    
    def upload_user_dict(self,input):
        for item in input:
            jieba.load_userdict(item)
    
    def getkey(self,strinput):
        words = pseg.cut(strinput)
        singer = ''
        name = ''
        for word, flag in words:
            if(flag == 'nr'):
                print('Singer is: %s'%word)
                singer+=word
            if(flag == 'nz'):
                print('Music name is: %s'%word)
                name+=word

            # print('%s,%s'%(word,flag))
        
        return (singer,name)



#自定义词典
userdict=[
    "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/nlu/script/analise/songs.txt",
    "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/nlu/script/analise/musician.txt"
]

#分词器
partical=Partical()


def callback(data):
    # rospy.loginfo(rospy.get_caller_id() + "[Partical Node] heard %s", data.isplay)
    partical.getkey(data.topic)

def listener():
    rospy.init_node('partical', anonymous=True)
    rospy.Subscriber("nlu/isplay_music", IsPlayMusic, callback)
    rospy.spin()

if __name__ == '__main__':
    #初始化结巴分词模块，上传用户词条
    partical.upload_user_dict(userdict)
    listener()