/*
 * XFonlineasr.h
 *
 *  Created on: 2017年1月3日
 *      Author: hntea
 */

#ifndef _XFWAKEUP_H
#define _XFWAKEUP_H

#include "../include/xfApiHead/qisr.h"
#include "../include/xfApiHead/msp_cmn.h"
#include "../include/xfApiHead/msp_errors.h"
#include "../include/xfApiHead/qivw.h"
#include "xfparams.h"
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>


using namespace std;
namespace Hntea{
class XFWakeup
{
    public:

    //回调函数
    static int cb_ivw_msg_proc( const char *sessionID, int msg, int param1, int param2, const void *info, void *userData )
    {
        if (MSP_IVW_MSG_ERROR == msg) //唤醒出错消息
        {
            cout<<"唤醒出错:param1 = "<<param1 <<endl;
        }
        else if (MSP_IVW_MSG_WAKEUP == msg) //唤醒成功消息
        {
            printf("唤醒成功：%s\n",info);
        }
        return 0;
    }

    void init(XfWakeupParams& param)
    {
         _param.lgi_param = param.lgi_param;
         _param.ssb_param = param.ssb_param;
         login(_param);
    }
    //登陆
    void login(XfWakeupParams& param){
      
        int ret = MSPLogin(NULL, NULL, _param.lgi_param.c_str());
        if (MSP_SUCCESS != ret)
        {
            cout<<"MSPLogin failed, error code: "<<ret<<endl;
        }else{
            cout<<"唤醒登录成功.."<<endl;
        }
        
    }

    //准备回话：_sid每次唤醒都要更新
    void prepare(){
        if(!_sid.empty())
            _sid.clear();

        int err_code = 0;
        // cout<< _param.ssb_param<<endl;
        _sid=QIVWSessionBegin(NULL, _param.ssb_param.c_str(), &err_code);
        if (err_code != MSP_SUCCESS)
        {
            printf(" [wakeup] QIVWSessionBegin failed! error code:%d\n",err_code);
        }
        // cout<<"_sid = "<<_sid<<endl;
        //注册回调函数
        err_code = QIVWRegisterNotify(_sid.c_str(), cb_ivw_msg_proc,NULL);
        if (err_code != MSP_SUCCESS)
        {
            printf("[wakeup] QIVWRegisterNotify failed! error code:%d\n",err_code);
        }
    }

    //开始识别
    void begin_rec_16B(vector<short>& block){
        int err_code = QIVWAudioWrite(_sid.c_str(), (const void *)&block[0],
            block.size()*2, MSP_AUDIO_SAMPLE_FIRST);
        if (MSP_SUCCESS != err_code)
		{
			printf("[wakeup] QIVWAudioWrite failed! error code:%d\n",err_code);
		}
        sleep_ms(2); 
    }
    //持续
    void hold_rec_16B(vector<short>& block){
        int err_code = QIVWAudioWrite(_sid.c_str(), (const void *)&block[0],
        block.size()*2, MSP_AUDIO_SAMPLE_CONTINUE);
        if (MSP_SUCCESS != err_code)
		{
			printf("[wakeup] QIVWAudioWrite failed! error code:%d\n",err_code);
		}
        sleep_ms(2); 
    }
    //结束
    void end_rec_16B(vector<short>& block)
    {
        int err_code = QIVWAudioWrite(_sid.c_str(), (const void *)&block[0],
        block.size()*2,  MSP_AUDIO_SAMPLE_LAST);
        if (MSP_SUCCESS != err_code)
		{
			printf("[wakeup] QIVWAudioWrite failed! error code:%d\n",err_code);
		}
        int ret = QIVWSessionEnd(_sid.c_str(), "topic end");
        sleep_ms(2); 
    }

    void run_rec_16B(vector<short>& block,int flag)
    {
        //todo
    }
protected:
    void sleep_ms(int ms)
    {
        usleep(ms * 1000);
    }
private:
    XfWakeupParams _param;
    string _sid;

};
}

#endif