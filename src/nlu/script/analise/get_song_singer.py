#!/usr/bin/env python
#-*- coding:utf-8 -*-

import sys
import re

sqlfile = '/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/nlu/script/analise/sql/music.sql'


class SQLParse(object):
    def __init__(self,sqlfile):
        self.file = sqlfile
        self.start_id = 0
        self.end_id = 0
        self.items = []
        self.music_name = []
        self.musician = []


    def __find_val_range(self):
        with open(self.file,'r') as fd:
            lines = fd.readlines()
        #find start
        for line in lines:
            ret = re.match('INSERT INTO',line)
            if(ret):
                self.start_id+=1
                break
            else:
                self.start_id+=1
        #find end
        for line in lines[self.start_id:]:
            end = re.search(r';$',line,)
            if(end):
                self.end_id+=1
                break
            else:
                self.end_id+=1
        self.items = lines[self.start_id:self.end_id]

    def __split_item(self):
        name = []
        singer = []
        for item in self.items:
            item = item.split(',')
            name.append(item[1])
            singer.append(item[3])
        for item in name:
            item = item.strip('\'').strip('').strip('')[2:]
            self.music_name.append(item)
        
        for item in singer:
            item = item.strip('\'')[2:]
            self.musician.append(item)

    def saveSongs(self,output):
        of = open(output,'w')
        for item in self.music_name:
            content = item+' '+'5'+' '+'nz\n'
            of.write(content)
        of.close()
    
    def saveMusician(self,output):
        of = open(output,'w')
        for item in self.musician:
            content = item+' '+'5'+' '+'nr\n'
            of.write(content)
        of.close()

    def prase(self):
        self.__find_val_range()
        self.__split_item()



# with open(sqlfile,'r') as fd:
#     lines = fd.readlines()


# index=0
# for line in lines:
#     ret = re.match('INSERT INTO',line)
#     if(ret):
#         index+=1
#         print index 
#         print line
#         break
#     else:
#         index+=1

# lists = []
# lists.append([1,2,3])
# print lists
# lists.append([2,3,4,5])
# print lists

parse = SQLParse(sqlfile)
parse.prase()
parse.saveSongs('songs.txt')
parse.saveMusician('musician.txt')