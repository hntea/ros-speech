#-*- coding:utf-8 -*-
import os
# music and chat


# datadir = os.path.abspath(os.curdir)+'/dataset/'
# c1music = 'train/music.txt'
# c2chat = 'train/chat.txt'

# c1tmusic = 'test/music.txt'
# c2tchat = 'test/chat.txt'
# testfile = datadir+'test.txt'

# savefile = datadir+'dataset.dat'


#sf = open(savefile,'w') #训练集
#tf = open(testfile,'w') #测试集

#load music txt
# with open(datadir+c1music,'r') as mf:
#     lines = mf.readlines()

# for line in lines:
#     line = line.split('\n')
#     txt =  "music\t"+"".join(line)+'\n'
#     sf.write(txt)

#load chat txt
# with open(datadir+c2chat,'rb') as cf:
#     clines = cf.readlines()

# for line in clines:
#     line = line.split()
#     ctxt = "chat\t"+"".join(line)+'\n'
#     sf.write(ctxt)
# sf.close()


datadir =  os.path.abspath(os.curdir)+'/dataset/'
trainc1 = datadir+'train/music.txt'
trainc2 = datadir+'train/chat.txt'
testc1 =  datadir+'test/music.txt'
testc2 =  datadir+'test/chat.txt'

testfile = datadir+'test.dat'
trainfile = datadir+'train.dat'

def loadmusic(inf,of):
    ofd = open(of,'w')
    with open(inf,'r') as f:
        lines = f.readlines()
    for line in lines:
        line = line.split('\n')
        txt =  "music\t"+"".join(line)+'\n'
        ofd.write(txt)
    ofd.close()

def loadchat(inf,of):
    ofd = open(of,'w')
    with open(inf,'rb') as ifd:
        lines = ifd.readlines()
    for line in lines:
        line = line.split()
        ctxt = "chat\t"+"".join(line)+'\n'
        ofd.write(ctxt) 


def loaddata(musicf,chatf,savef):
    sf = open(savef,'w')
    #load music
    with open(musicf,'r') as mf:
        lines = mf.readlines()
    for line in lines:
        line = line.split('\n')
        txt =  "music\t"+"".join(line)+'\n'
        sf.write(txt)    
    #load chat
    with open(chatf,'r') as cf:
        clines = cf.readlines()
    for line in clines:
        line = line.split()
        ctxt = "chat\t"+"".join(line)+'\n'
        sf.write(ctxt)
    sf.close()

#处理训练集
loaddata(trainc1,trainc2,trainfile)
loaddata(testc1,testc2,testfile)