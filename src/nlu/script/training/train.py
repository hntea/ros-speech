#-*- coding:utf-8 -*-
import os
from tgrocery import Grocery

dataset = '/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/nlu/script/training/dataset/dataset.dat'
 # 新开张一个杂货铺（别忘了取名）
grocery = Grocery('sample')
# 训练文本可以用列表传入
# train_src = [
#     ('education', '名师指导托福语法技巧：名词的复数形式'),
#     ('education', '中国高考成绩海外认可 是“狼来了”吗？'),
#     ('sports', '图文：法网孟菲尔斯苦战进16强 孟菲尔斯怒吼'),
#     ('sports', '四川丹棱举行全国长距登山挑战赛 近万人参与')
# ]
# grocery.train(train_src)
#也可以用文件传入（默认以tab为分隔符，也支持自定义）
#grocery.train(dataset)
# 保存模型
#grocery.save()
# 加载模型（名字和保存的一样）
new_grocery = Grocery('sample')
new_grocery.load()
# 预测
print new_grocery.predict('放一首歌来听')
print new_grocery.predict('你叫什么名字')
print new_grocery.predict('吃饱没有')
print new_grocery.predict('周杰伦')
print new_grocery.predict('黑色衣服好看')
print new_grocery.predict('王力宏')
print new_grocery.predict('波哥')
print new_grocery.predict('播歌')
print new_grocery.predict('我要听张含韵的歌')
print new_grocery.predict('放一首：富士山下')
print new_grocery.predict('点播：兄弟')
# 测试
# 测试
# 测试
# test_src = [
#     ('education', '福建春季公务员考试报名18日截止 2月6日考试'),
#     ('sports', '意甲首轮补赛交战记录:米兰客场8战不败国米10年连胜'),
# ]
#new_grocery.test(test_src)
# 输出测试的准确率

# 同样可支持文件传入
#new_grocery.test('test_ch.txt')
# 自定义分词模块（必须是一个函数）
#custom_grocery = Grocery('custom', custom_tokenize=list)