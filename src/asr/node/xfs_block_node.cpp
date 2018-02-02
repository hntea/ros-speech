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

#include "pre_processer/Asrdata.h"

using namespace std;
using namespace Hntea;



ros::Publisher pub;
Hntea::ConfigResolver parser;
Hntea::XFonlineasr xfasr;

enum VADSTATE{
    QUITE=0,
    MAYBESTART,
    START,
    HOLD,
    MAYBEEND,
    END
};



void streamCallback(const pre_processer::Asrdata& msg)
{
	std::vector<int16_t> vec;
    string result;
    //转换成16位整形
    for(auto item:msg.source){
        short sample = item;
        vec.push_back(sample);
    }

    if(msg.vad_state == VADSTATE::END){
		
        //cout<<"结束"<<endl;
        xfasr.runasr(vec,result,true);
		printf("[xfs_asrb] result = %s\n",result.c_str());
		std_msgs::String res;
		res.data = result;
		pub.publish(res);
    }else{
        //cout<<"开始"<<endl;
        xfasr.runasr(vec,result,false);
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

	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/asrbrige/source", 50, streamCallback);
	pub = n.advertise<std_msgs::String>("asr/xf/b_res",50);
	ros::spin();
	return 0;
}
