#-*- coding:utf-8 -*-
import os
# music and chat


print 

datadir = os.path.abspath(os.curdir)+'/dataset/'
c1music = 'music.txt'
c2chat = 'chat.txt'

savefile = datadir+'dataset.dat'


sf = open(savefile,'w')

#load music txt
with open(datadir+c1music,'r') as mf:
    lines = mf.readlines()

for line in lines:
    line = line.split('\n')
    txt =  "music\t"+"".join(line)+'\n'
    sf.write(txt)


#load chat txt
with open(datadir+c2chat,'rb') as cf:
    clines = cf.readlines()

for line in clines:
    line = line.split()
    ctxt = "chat\t"+"".join(line)+'\n'
    sf.write(ctxt)

sf.close()