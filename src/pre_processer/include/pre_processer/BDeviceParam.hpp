#ifndef _BDEVICEPARAM_HPP
#define _BDEVICEPARAM_HPP

//该文件主要用于管理声卡配置参数

#include <iostream>
#include <assert.h>

using namespace std;
namespace Hntea
{
//声卡模式    
enum MODE
{
    PLAYER = 0,
    RECORDER ,
};
//声卡配置参数
struct BDeviceParam
{
    unsigned int channels;
    unsigned int depth;
    unsigned int freq;
    MODE mode;
    string name;

    BDeviceParam(char c,char dep,int rate,MODE m,string n):channels(c),depth(dep),
    freq(rate),mode(m),name(n){};
};
}

#endif