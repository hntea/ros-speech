#!/usr/bin/env python
#-*- coding:utf-8 -*-
import sys
import rospy
from nlu.srv import *
from std_msgs.msg import String
import jieba 
import jieba.posseg as pseg


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
                print('Music name is: %s' %word)
                name+=word

            print('%s,%s'%(word,flag))
        
        return singer,name


#分词器
partical=Partical()

userdict=[
    ["/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/nlu/script/analise/musician.txt"],
    ['/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/nlu/script/analise/songs.txt']
]


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
    if ret == 1:
        singer,song = partical.getkey(data.data)
        print singer
        print song
    

def is_music():
    rospy.init_node('nlu_is_music_client', anonymous=True)
    rospy.Subscriber("asr/xf/b_res", String, callback)
    rospy.spin()

if __name__ == "__main__":
    '''
    节点说明：
    对识别结果进行是否在本地播放音乐的预判
    '''

    #初始化结巴分词模块，上传用户词条
    partical.upload_user_dict(userdict)
    #初始化客户节点
    is_music()