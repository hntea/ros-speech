#-*- coding:utf-8 -*-
import os
from tgrocery import Grocery

text_set =  '/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/nlu/script/training/dataset/test.dat'

modelsave = 'model'
new_grocery = Grocery(modelsave)
new_grocery.load()
# 预测
# ret = new_grocery.predict('放一首歌来听').predicted_y
# print "放一首歌吧"+str(new_grocery.predict('放一首歌来听').predicted_y)
# print new_grocery.predict('你叫什么名字')
# print new_grocery.predict('吃饱没有')
# print new_grocery.predict('周杰伦')
# print new_grocery.predict('黑色衣服好看')
# print new_grocery.predict('王力宏')
# print new_grocery.predict('波哥')
# print new_grocery.predict('播歌')
# print new_grocery.predict('我要听张含韵的歌')
# print new_grocery.predict('放一首：富士山下')
# print new_grocery.predict('点播：兄弟')
# print new_grocery.predict('听歌')
# print new_grocery.predict('听歌。')
# print new_grocery.predict('我要听歌')
# print new_grocery.predict('我要听音乐。')
# print new_grocery.predict('播放歌曲。')
# print new_grocery.predict('音乐播放。')
# print new_grocery.predict('Music.')
# print new_grocery.predict('音乐电台。')
# print new_grocery.predict('单曲循环当前歌曲')
# print new_grocery.predict('顺序播放歌曲。')
# test_src = [
#     ('education', '福建春季公务员考试报名18日截止 2月6日考试'),
#     ('sports', '意甲首轮补赛交战记录:米兰客场8战不败国米10年连胜'),
# ]
#new_grocery.test(test_src)
# 输出测试的准确率

# 同样可支持文件传入
result = new_grocery.test(text_set)
result.show_result()
# 自定义分词模块（必须是一个函数）
#custom_grocery = Grocery('custom', custom_tokenize=list)