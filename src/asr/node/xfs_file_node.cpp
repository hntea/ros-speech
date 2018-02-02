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

using namespace std;
using namespace Hntea;

ros::Publisher pub;
Hntea::ConfigResolver parser;
Hntea::XFonlineasr xfasr;



void callback(const std_msgs::String& msg)
{
    string file(msg.data);
    string ret;
    cout<<file<<endl;
	xfasr.runasr(file,ret);
    cout<<"[xfs_asrf] = "<< ret<<endl;
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
	ros::init(argc, argv, "xfs_asrf");

	// 依照配置文件配置服务
	std::string configfile;
	ros::param::param<std::string>("~configfile",configfile,defaultFile());
    parser.setCfgfile(configfile);
    parser.process();
    
    XfOnlineASR params =  parser.getXfOnlineParams();
    XfBasic login  = parser.getXfBasic();
    xfasr.initcfg(params,login);

	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/asrbrige/file", 50, callback);
	pub = n.advertise<std_msgs::String>("asr/xf/f_res",50);
	ros::spin();
	return 0;
}
