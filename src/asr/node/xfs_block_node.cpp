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
#include "asr/IsWakeup.h"
using namespace std;
using namespace Hntea;



ros::Publisher pub;
ros::Publisher pub2;
Hntea::ConfigResolver parser;
Hntea::XFonlineasr xfasr;
Hntea::XFWakeup xfwk;

enum VADSTATE{
    QUITE=0,
    MAYBESTART,
    START,
    HOLD,
    MAYBEEND,
    END
};

static bool is_wakeup = false;  
void wakeupCallback(const asr::IsWakeup& msg)
{
    cout<<"设备唤醒.."<<endl;
    if(msg.isWakeup)
        is_wakeup = true;
}

void streamCallback(const pre_processer::Asrdata& msg)
{
    if(is_wakeup){

	std::vector<int16_t> vec;
    string result;
    //转换成16位整形
    for(auto item:msg.source){
        short sample = item;
        vec.push_back(sample);
    }

    //识别过程
    if(msg.vad_state == VADSTATE::END){
        //cout<<"结束"<<endl;
        xfasr.runasr(vec,result,true);
        printf("[xfs_asrb] result = %s\n",result.c_str());
        std_msgs::String res;
        res.data = result;
        pub.publish(res);
        is_wakeup = false;  //识别结束后，再次设置成休眠模式
        asr::IsWakeup msg2;
        msg2.isWakeup = 0;
        pub2.publish(msg2); //通知唤醒节点，再次启动唤醒功能
    }else{
        //cout<<"开始"<<endl;
        xfasr.runasr(vec,result,false);
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
	ros::init(argc, argv, "xfs_asrb");

	// 依照配置文件配置服务
	std::string configfile;
	ros::param::param<std::string>("~configfile",configfile,defaultFile());
    parser.setCfgfile(configfile);
    parser.process();
    
    XfOnlineASR params =  parser.getXfOnlineParams();
    XfBasic login  = parser.getXfBasic();
    xfasr.initcfg(params,login);
    //无法在同一个进程中登录
    // XfWakeupParams wakeup_params = parser.getXfWakeupParams();
    // xfwk.init(wakeup_params);

	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/asrbrige/source", 50, streamCallback);
 	ros::Subscriber sub2 = n.subscribe( "asr/xf/wakeup", 50, wakeupCallback);  
	pub = n.advertise<std_msgs::String>("asr/xf/b_res",50);
    pub2 = n.advertise<asr::IsWakeup>("asr/isdone",50);
	ros::spin();
	return 0;
}
