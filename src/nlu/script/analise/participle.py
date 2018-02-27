#!/usr/bin/env python
#-*- coding:utf-8 -*-

import jieba 
import jieba.posseg as pseg

# seg_list = jieba.cut("给我来一首王力宏的落叶归根", cut_all=False)
# print("Full Mode: " + "/ ".join(seg_list))  # 全模式
# seg_list = jieba.cut("我想听周杰伦的听妈妈的话", cut_all=False)
# print("Full Mode: " + "/ ".join(seg_list))  # 全模式

# words = pseg.cut("我想听周杰伦的听妈妈的话")
# for word, flag in words:
#     print('%s %s' % (word, flag))

# words = pseg.cut("刘德华的冰雨")
# for word, flag in words:
#     print('%s %s' % (word, flag))

userdict=[
    "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/nlu/script/analise/songs.txt",
    "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/nlu/script/analise/musician.txt"
]
def upload_user_dict(input):
    for item in input:
        jieba.load_userdict(item)
upload_user_dict(userdict)

# jieba.load_userdict('songs.txt')
# jieba.load_userdict('musician.txt')
seg_list = jieba.cut("我想听周杰伦的听妈妈的话", cut_all=False)
print("Full Mode: " + "/ ".join(seg_list))  # 全模式
seg_list = jieba.cut("我想听周末我们去海边", cut_all=False)
print("Full Mode: " + "/ ".join(seg_list))  # 全模式

def getkey(strinput):
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
    return singer,name

# print getkey("播一首歌")
print "".join(getkey("想听陈奕迅的十年")[1])
print getkey("我想听周杰伦的听妈妈的话")
