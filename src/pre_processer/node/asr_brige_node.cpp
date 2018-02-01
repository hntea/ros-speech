#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <ros/ros.h>
#include <pre_processer/OneChannelDataset.h>
#include "pre_processer/Asrdata.h"
#include "std_msgs/String.h"
#include "aquila/global.h"
#include "aquila/source/WaveFile.h"
#include "../include/pre_processer/Bvad.hpp"
#include <fstream>
#include <list>
#include <atomic>
#include <pthread.h>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

using namespace std;

namespace Hntea{
class AsrBrige{
    public:
        AsrBrige(){
            if(m_wkdir.empty())
                mkdefdir();
            //预留配置目录项
        }
        ~AsrBrige(){
            cout<<"asr brige destory!"<<endl;
        }

        /*
        函数功能：设置前后缓存长度
        */
        void setBuflen(size_t plen,size_t blen){
            m_prebuflen = plen;
            m_backbuflen = blen;
        }


        void setConfigInfo(size_t plen,size_t blen,string wkdir)
        {
            m_prebuflen = plen;
            m_backbuflen = blen;
            // if(wkdir == "default")
            //     ;//todo
        }

        /*
        函数功能：前项缓存
        */        
        void loadDataToPrebuf(const vector<double>& source)
        {
            if(m_prebuf.size() < m_prebuflen)
                m_prebuf.push_back(source);
            else{
                m_prebuf.pop_front();
                m_prebuf.push_back(source);
            }
        }
        /*
        函数功能：将数据装载到voicebuf中
        说明：要从检测到起始端点信号开始才能使用这个函数
        */
        void loadDataToVoicebuf(const vector<double>& source)
        {
            m_voicebuf.push_back(source);
        }
        
        /*
        函数功能：后向缓存
        */
        void loadDataToBackbuf(const vector<double>& source){
            if(m_backbuf.size()<m_backbuflen)
                m_backbuf.push_back(source);
        }

        /*
        将缓存中的数据装换成16bit再装入allbuf中
        */
        void loadbufDataToAllbuf16Bit(const deque<vector<double> > buf ){
            for(auto block:buf){
                for(auto item:block)
                {
                    short tmp = item;
                    m_allbuf_16Bit.push_back(item);
                }
            }
        }

        /*
        将所有数据加载到allbuf中　16bit
        */
        void loadAllToAllbuf16Bit(){
            //1.加载前项缓存
            loadbufDataToAllbuf16Bit(m_prebuf);
            //2.加载有效语音帧
            loadbufDataToAllbuf16Bit(m_voicebuf);
            //3.加载后向缓存
            loadbufDataToAllbuf16Bit(m_backbuf);
        }

        /*
        清除所有缓存数据
        */
        void clearAllbuf(){
            m_allbuf_16Bit.clear();
            m_backbuf.clear();
            m_prebuf.clear();
            m_asrbuf.clear();
            m_voicebuf.clear();
        }
        /*
        */
        void loadData16BitToPcmFile(const string& file)
        {
            std::ofstream fs;
		    fs.open(file.c_str(), std::ios::out | std::ios::binary);
            loadAllToAllbuf16Bit();
            fs.write((const char*)&m_allbuf_16Bit[0],2*m_allbuf_16Bit.size());
	        fs.close();
            cout<<"File ["<<m_pcm<<"]"<<" has been Created!"<<endl;
            clearAllbuf();
        }
        /*
        将数据加载到wav文件中
        参数说明：
            ＠file：文件名
            ＠rate: 采样率
            ＠channel:通道数
            ＠depth:样本精度
        */
        void loadDataToWavFile(string file,size_t rate,size_t channel=1,size_t depth=16)
        {
            if(!m_allbuf_64Bit.empty())
                m_allbuf_64Bit.clear();

            //1.前向缓存
            for(auto block:m_prebuf)
            {
                for(auto item:block)
                    m_allbuf_64Bit.push_back(item);
            }
            //2.语音帧缓存
            for(auto block:m_voicebuf)
            {
                for(auto item:block)
                    m_allbuf_64Bit.push_back(item); 
            }
            //3.后向缓存
            for(auto block:m_backbuf)
            {
                for(auto item:block)
                    m_allbuf_64Bit.push_back(item); 
            }
            //4.使用aquial库
            Aquila::SignalSource signal(m_allbuf_64Bit,rate);
            cout<<file<<endl;
            Aquila::WaveFile wav_file(file);
            wav_file.save(signal,file);
            
            //清空数据
            if(!m_allbuf_64Bit.empty()){
                cout<<m_allbuf_64Bit.size()<<endl;
                 m_allbuf_64Bit.clear();
            }
               
            cout<<"File ["<<m_wav<<"]"<<" Created!"<<endl;
        }

    /*
	 * 函数功能：分配文件名
	 * 参数说明：
	 * 			workspace:工作目录
	 * 			max_id:缓存大小
	 * */
	 void allocalFile(std::string workspace,const int max_id = 10){

		std::string wav = ".wav";
		std::string pcm = ".pcm";
		std::stringstream s_wav;
		std::stringstream s_pcm;

		if(m_fileID == max_id){
			m_fileID = 0;
		}
		//这部分不是线程安全的。
		s_wav<<workspace<<m_fileID<<wav;
		s_pcm<<workspace<<m_fileID<<pcm;
		m_wav = s_wav.str();
		m_pcm = s_pcm.str();
		m_fileID++;
	}

    string getWkdir(){
        return m_wkdir;
    }
    string getWavfile(){
        return m_wav;
    }
    string getPcmfile(){
        return m_pcm;
    }
private:

    /*
    函数功能：创建默认工作目录
    */
	void mkdefdir(){
		int err;
        //获取home 路径
		struct passwd *pw = getpwuid(getuid());
		const char *homedir = pw->pw_dir;
		std::string path(homedir);
        //建立一级目录
        path+="/ros-speech";
        //cout<<path<<endl;
        err = mkdir(path.c_str(),0775);
        //建立二级目录
        path+="/audio";
        //cout<<path<<endl;
        err = mkdir(path.c_str(),0775);
        m_wkdir = path+"/";
	}

    //todo
    // void mkdirs(){
    //     int dirs = 0;
    //     vector<int> index;
    //     vector<string> subdir;
    //     if(!m_wkdir.empty()){
    //         idx = 0;
    //         for(auto item:m_wkdir){
    //             if(item == '/'){
    //                 dirs++;
    //                 index.push_back(idx);
    //             }
    //             idx++;
    //         }
    //     }

    //     while(dirs >= 1){
    //         string dir = m_wkdir.substr(0,index[]) 
    //     }
    // }

    void mkcfgdir(){
 		int err;

        //获取home 路径
		struct passwd *pw = getpwuid(getuid());
		const char *homedir = pw->pw_dir;
		std::string path(homedir);       
    }

    public:
        deque<vector<double> > m_prebuf;     //前向帧缓存
        deque<vector<double> > m_voicebuf;  //有效语音缓存
        deque<vector<double> > m_backbuf;    //后项帧缓存
        deque<vector<double> > m_asrbuf;     //识别音频块
        vector<double> m_allbuf_64Bit;        //存放从起始到结束的音频数据（用于文件）
        vector<short> m_allbuf_16Bit;       
    
    private:
        string m_wav,m_pcm;         //文件名
        string m_wkdir;             //工作目录
        size_t m_fileID;            //文件索引
        size_t m_prebuflen,m_backbuflen;
        Aquila::SignalSource m_signal;
};
};



using namespace Hntea;
Hntea::AsrBrige brige;
ros::Publisher pub1,pub2;

void callback(const pre_processer::OneChannelDataset &msgs){
   pre_processer::OneChannelDataset dataset = msgs;
   pre_processer::Asrdata p2msg;
   //加载前向缓存
   if(dataset.vad_state == MFCC_STATE::QUIET || dataset.vad_state == MFCC_STATE::MAYBE_START)
   {
        brige.loadDataToPrebuf(dataset.s_data);
        //cout<<"加载前向缓存"<<endl;
   }

   //加载语音数据)
   if(dataset.vad_state==START || dataset.vad_state==HOLD || dataset.vad_state==MAYBE_END)
   {
        brige.loadDataToVoicebuf(dataset.s_data);
        //cout<<"加载语音帧　state = "<<dataset.vad_state<<endl;
        //实时音频流
        if( brige.m_asrbuf.size()<brige.m_prebuf.size()){
            for(auto block:brige.m_prebuf)
            {
                brige.m_asrbuf.push_back(block);
            }
        }
        brige.m_asrbuf.push_back(dataset.s_data);
        //发布有效语音流
        pre_processer::Asrdata p2msg;
        p2msg.source = brige.m_asrbuf.front();
        p2msg.vad_state = dataset.vad_state;
        pub2.publish(p2msg);
        //cout<<"发布语音帧"<<endl;
        brige.m_asrbuf.pop_front();
   }

   //加载后向缓存
   if(dataset.vad_state == END)
   {
        brige.loadDataToBackbuf(dataset.s_data);
         //cout<<"加载后缓存"<<endl;
        //将未发布出去的数据发布
        while(!brige.m_asrbuf.empty()){
         p2msg.source = brige.m_asrbuf.front();   
         pub2.publish(p2msg);
         brige.m_asrbuf.pop_front();
        }
         //cout<<"发布语音帧"<<endl;
        p2msg.source = brige.m_backbuf.front();
        p2msg.vad_state = dataset.vad_state;
        brige.m_backbuf.pop_front();
        pub2.publish(p2msg);

        //最后生成文件
        brige.allocalFile(brige.getWkdir());
        string pcmfile = brige.getPcmfile();
        std_msgs::String p1msg;
        p1msg.data = pcmfile.c_str();
        brige.loadData16BitToPcmFile(pcmfile);
        pub1.publish(p1msg);
   }

}

int main(int argc,char** argv)
{

    ros::init(argc, argv, "asr_brige");
    ros::NodeHandle nh;
    
    string wkdir;
    int plen;
    ros::param::param<string>("~wkdir", wkdir, "/ros-speech/audio/");
    ros::param::param<int>("~prebuf_len", plen,20);
    
    brige.setConfigInfo(plen,plen+1,"default");  
    
    ros::Subscriber sub = nh.subscribe("pre/dataset", 50, callback);
    pub1 = nh.advertise<std_msgs::String>("asrbrige/file", 50);
    pub2 = nh.advertise<pre_processer::Asrdata>("asrbrige/source",50);
    ros::spin();
    return 0;
}