#!/usr/bin/env python
#-*- coding:utf-8 -*-

import jieba 
import jieba.posseg as pseg

#自定义词典
userdict=[
    "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/nlu/script/analise/songs.txt",
    "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/nlu/script/analise/musician.txt"
]

class MusicInfo(object):
    '''
    对结巴分词工具在封装，主要提取输入语句的歌手和歌名
    '''
    def __init__(self):
        self.__upload_user_dict(userdict)
    
    def __upload_user_dict(self,input):
        '''
        上传自定义词典
        '''
        for item in input:
            jieba.load_userdict(item)
    
    def getkey(self,strinput):
        '''
        提取歌手和歌曲名并返回
        '''
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