#include <ros/ros.h>
#include <assert.h>
#include <vector>
#include <queue>


#include "../include/pre_processer/OneChannelDataset.h"
#include "../include/pre_processer/BDeviceParam.hpp"
#include "../include/pre_processer/NormalMic.hpp"
#include "../include/pre_processer/PreEmphasis.hpp"
#include "../include/pre_processer/HanMingWin.hpp"
#include "../include/pre_processer/FeatureSet.hpp"
#include "../include/pre_processer/Bvad.hpp"
#include "../include/pre_processer/MfccVad.hpp"


using namespace std;
using namespace Hntea;
class PreProcesser{
public:
	PreProcesser(){
        init();  
	}
	~PreProcesser(){
		
	}

    //对象初始化
    void init()
    {
		//使用参数解析器，初始化块大小 32ms
        ros::param::param<int>("~block_size", m_size, 512);
        ros::param::param<int>("~channels", m_channle, 1);
        ros::param::param<int>("~depth", m_sample, 16);
        ros::param::param<int>("~sample_rate", m_rate, 16000);
        ros::param::param<std::string>("~name", m_name, "default");//plughw:2,0

        BDeviceParam* param = new BDeviceParam(m_channle,m_sample,m_rate,RECORDER,m_name);
        //声卡配置
        if(m_mic.set_param(param))
            showConfig(param,m_size);       
        else
            cerr<<"Mic init err!"<<endl;

        //申请缓存空间
        m_data.resize(m_size);
        //发布消息，缓存空间 50，true 表示其它节点个同步接受信息。
        m_pub = m_nh.advertise<pre_processer::OneChannelDataset>("pre/dataset", 50, true);

        m_step = m_size/2;
        m_frame.resize(m_step);

        //重新消息定义数组大小
        msg.size = m_size;
        msg.s_data.resize(m_step);
        msg.p_data.resize(m_size);

        //初始化窗口
        mp_hanmingwin = new HanMingWin(m_size);

        //初始化vad算法对象
        mp_vad = new MfccVad(30,30);


        //初始化特征相关参数
        m_features.setFreq(m_rate);

        //填充窗口
        fillFirstWindow();
        cout<<"init success!"<<endl;
        
    }


    //执行预处理过程
    void run()
    {
        uint64_t count = 0;
        while(ros::ok())
        {
           
            //预加重
            m_emphasis.preEmphasis(m_data,m_data,0.98);
            m_features.setData(m_data);
            double zero_crossing = m_features.getZeroCrossing();

            //加窗
            mp_hanmingwin->addWindow(m_data);
            
            //特征提取
            m_features.setData(m_data);
            double energy = m_features.getEnergy();
            vector<double> mfcc = m_features.getMfcc(12);
            ((MfccVad*)mp_vad)->updateMfcc(mfcc);
            //端点检测
            ((MfccVad*)mp_vad)->runvad();

            //构造消息并发布
            msg.p_data = m_data;// 处理后的数据，源数据在帧移函数中加载
            msg.energy=energy;
            msg.zero=zero_crossing;
            msg.mfcc=mfcc;
            msg.mfccl2=((MfccVad*)mp_vad)->getMfccL2();
            msg.vad_state = ((MfccVad*)mp_vad)->getVadState();
			m_pub.publish(msg);
           
            //帧移
            frameShift();
			ROS_INFO_THROTTLE(60, "[Node PreProcesser],Well Done!");
			ros::spinOnce();
        }     
    }

    void showConfig(BDeviceParam* param,size_t block)
    {
        assert(param != NULL);
        cout<<"[pre_process]:block size: "<<block<<endl;
        cout<<"[pre_process]:channels: "<<param->channels<<endl;
        cout<<"[pre_process]:rate: "<<param->freq<<endl;
        cout<<"[pre_process]:depth: "<<param->depth<<endl;
        cout<<"[pre_process]:name: "<<param->name<<endl;
    }

    //初始化填充窗口
    void fillFirstWindow()
    {
        m_mic.read(&m_frame[0],m_step);
        m_frames.push(m_frame);   
        //填充缓存
        for(int i=0;i<m_step;i++)
             m_data[i] = m_frame[i];

        m_mic.read(&m_frame[0],m_step);
        m_frames.push(m_frame);  
        for(int i=m_step;i<m_size;i++){
            m_data[i] =  m_frame[i-m_step] ;
            msg.s_data[i-m_step] = m_data[i];   //填充原始数据
        }
        
    }

    //帧移
    void frameShift()
    {
        m_frames.pop();
        if(!m_frames.empty())
        {
            vector<short> tmp = m_frames.front();
            for(int i=0;i<tmp.size();i++)
                m_data[i] = tmp[i];
        }
        m_mic.read(&m_frame[0],m_step);

        for(int i=m_step;i<m_size;i++)
        {
            msg.s_data[i-m_step] =m_frame[i-m_step];    //装载源数据
            m_data[i] = m_frame[i-m_step];
        }

        m_frames.push(m_frame);
    }

private:
    ros::NodeHandle m_nh;
    ros::Publisher m_pub;
    NormalMic m_mic;
    std::string m_name;
    int   m_size,m_channle,m_sample, m_rate;

    int m_step;
    vector<short> m_frame;
    queue<vector<short> > m_frames;
    vector<double> m_data;
    PreEmphasis m_emphasis;   
    FeatureSet m_features;
    HanMingWin* mp_hanmingwin;
    Bvad*   mp_vad;


    pre_processer::OneChannelDataset msg;   //自定义消息
};


int main(int argc, char **argv)
{
  ros::init(argc, argv, "preprocesser");
  PreProcesser process;
  process.run();
}