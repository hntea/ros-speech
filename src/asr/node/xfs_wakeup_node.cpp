#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include "../include/asr/xunfei/lib/XFonlineasr.h"
#include "../include/asr/xunfei/lib/xfparams.h"
#include "../include/asr/xunfei/lib/ConfigResolver.h"
#include "../include/asr/xunfei/lib/XFwakeup.h"
#include "asr/IsWakeup.h"
#include "pre_processer/Asrdata.h"
// #include "asr/IsWakeup.h"
using namespace std;
using namespace Hntea;



ros::Publisher pub;
Hntea::ConfigResolver parser;
Hntea::XFWakeup xfwk;

enum VADSTATE{
    QUITE=0,
    MAYBESTART,
    START,
    HOLD,
    MAYBEEND,
    END
};




void isdoneCallback(const asr::IsWakeup& msg){
    if(msg.isWakeup==0){
        xfwk.set_wakeup("sleep");
        cout<<"一轮识别结束，设置设备休眠"<<endl;
    }
      
}

void Callback(const pre_processer::Asrdata& msg)
{
    static bool reset = true;
    string wakeup = xfwk.get_wakeup();

    std::vector<int16_t> vec;
    string result;
    //转换成16位整形
    for(auto item:msg.source){
        short sample = item;
        vec.push_back(sample);
    }

    if(wakeup == "wakeup" && reset ==false)     //注意得到唤醒结果时当前帧可能不是处于最终状态
    {     
        if((msg.vad_state == VADSTATE::HOLD || msg.vad_state == VADSTATE::MAYBEEND))
        {
            xfwk.hold_rec_16B(vec);
        }
                
        if(msg.vad_state == VADSTATE::END)
        {
            xfwk.end_rec_16B(vec);
            cout<<"唤醒！"<<endl;
            asr::IsWakeup msg;
            msg.isWakeup = 1;
            pub.publish(msg);
            reset = true;
        }
    }

    if(wakeup != "wakeup")
    {   
        if(reset){
            // cout<<"准备唤醒"<<endl;
            xfwk.prepare();
            xfwk.begin_rec_16B(vec);
            reset = false;
        }
        
        if((msg.vad_state == VADSTATE::HOLD || msg.vad_state == VADSTATE::MAYBEEND)&&!reset)
        {
            xfwk.hold_rec_16B(vec);
            // cout<<"唤醒中........."<<endl;
        }
        
        if(msg.vad_state == VADSTATE::END)
        {
            xfwk.end_rec_16B(vec);
            cout<<"请先唤醒：小红小红"<<endl; //注意唤醒结束后并不会立马得到结果！
            reset = true;
        }
    }
}

/*
 * 获取默认配置文件
 * */
std::string defaultFile(){
	//获取home 路径
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	std::string path = homedir;
	path+="/ros-speech/config/config.json";
	return path;
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "xfs_wakeup");

	// 依照配置文件配置服务
	std::string configfile;
	ros::param::param<std::string>("~configfile",configfile,defaultFile());
    parser.setCfgfile(configfile);
    parser.process();
    
    XfWakeupParams params = parser.getXfWakeupParams();
    xfwk.init(params);
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/asrbrige/source", 1000, Callback);
    ros::Subscriber sub2 = n.subscribe("/asr/isdone", 1000, isdoneCallback);
	pub = n.advertise<asr::IsWakeup>("asr/xf/wakeup",50);
	ros::spin();
	return 0;
}
