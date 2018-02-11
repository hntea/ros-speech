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

#include "pre_processer/Asrdata.h"

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


static bool reset = true;
void Callback(const pre_processer::Asrdata& msg)
{
	std::vector<int16_t> vec;
    string result;
    //转换成16位整形
    for(auto item:msg.source){
        short sample = item;
        vec.push_back(sample);
    }
    
    if(reset){
        cout<<"准备唤醒"<<endl;
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
         cout<<"唤醒结束"<<endl;
         reset = true;
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
	// pub = n.advertise<std_msgs::String>("asr/xf/b_res",50);
	ros::spin();
	return 0;
}
