#ifndef _MFCCVAD_HPP
#define _MFCCVAD_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <numeric>
#include "Bvad.hpp"

namespace Hntea{

    class MfccVad:public Bvad
    {
        public:
            MfccVad(){};
            
            /*
            参数说明：
            @noise_count:背景噪声帧数
            @end_count:后端点延时计数
                延时时间　＝　end_count*每一帧时长
            */
            MfccVad(size_t noises_count,size_t end_count){
                init(noises_count,end_count);
            };
            
            /*
            函数功能：初始化
            参数说明：
                noises:假设前noises帧为噪声
                end_count:后端点延长计数　
            */
            void init(size_t noises,size_t end_count)
            {
                m_noise_frames = noises;
                m_is_noise_update = false;
                m_state = QUIET;
                m_background_noise.clear();
                m_holdcount=0;
                //用配置文件设置
                m_holdtime_cfg=end_count;   
                m_low_cfg = 0.4;
                m_up_cfg = 0.7;     
            }   

            void setThreshold(double low,double up){
                m_low_threshold = m_noise_level + low;
                m_up_threshold = m_noise_level + up;
            }

            /*
            更新背景噪声：
            */
            void updateNoise(){
                static bool is_firstframe = true;
                if(is_firstframe){
                    m_noise_level = m_l2;
                    setThreshold(m_low_cfg,m_up_cfg);
                    is_firstframe=false;
                }
                  
                if(m_state == QUIET)
                {
                    if(!m_background_noise.empty()){
                        if(m_background_noise.size() == m_noise_frames){
                            m_is_noise_update = true;
                            m_background_noise.pop_front();
                        }
                    }
                    m_background_noise.push_back(m_l2); 
                }
                if(m_is_noise_update){
                    m_noise_level = accumulate(m_background_noise.begin(),m_background_noise.end(),0.0)/m_noise_frames;
                    setThreshold(m_low_cfg,m_up_cfg);
                    m_is_noise_update = false;
                }
            }
            /*
            函数功能：更新MFCC数据
            */   
            void updateMfcc(const vector<double>& mfcc){
                m_mfcc = mfcc;
              //  __cmn(m_mfcc,m_mfcc); 使用这种方法导致只有最后计算的l2值不变（精度问题）
                m_l2 = __caculateMfccL2();
                updateNoise();  //更新噪声缓存
                runvad();
                m_mfcc.clear();
            }

            double getMfccL2(){
                return m_l2;
            }
            int getVadState(){
                return m_state;
            }

            virtual bool isQuiet(){
                if(m_state == END || m_state == QUIET){
                    if(m_l2 > m_low_threshold)
                    {
                       // m_plus = false; //关闭触发条件，使状态进入循环
                        m_state = MAYBE_START;
                        //cout<<"[isQuite]: MayBe Start!"<<endl;
                        return true;
                    }
                    else{
                        m_state = QUIET;
                        return false;
                    }
                }

            }

            virtual bool isStart(){
                if(m_state == MAYBE_START){
                    if(m_l2 > m_up_threshold){
                        m_state = START;
                        cout<<"[isStart] Start!"<<endl;
                        return true;
                    }
                    else{
                        m_state = QUIET;
                        //cout<<"[isStart] Is Quiet!"<<endl;
                        return false;
                    }
                }
                  
            }

            virtual bool isHold(){
                if(m_state == START && m_l2 > m_low_threshold){
                     m_state = HOLD;
                     cout<<"[isHold] HOLD!"<<endl;
                    return true;
                }
                else if (m_state == HOLD && m_l2 < m_low_threshold){
                    //cout<<"[isHold] MAYBE_END"<<endl;
                    m_state = MAYBE_END;
                    return false;
                }
                    
            }

            virtual bool isEnd(){
                if(m_state == MAYBE_END)
                {
                    if(m_l2 < m_low_threshold)
                        m_holdcount++;
                    //计数结束前又出现端点信号
                    if(m_l2 > m_up_threshold)
                        m_holdcount = 0;

                    if(m_holdtime_cfg == m_holdcount)
                    {
                         m_state = END;
                         m_holdcount = 0;
                         cout<<"End"<<endl;
                         return true;
                    }
                }else{
                    return false;
                }
            }

            void runvad()
            {
                bool ret;
                ret = isQuiet();
                ret = isStart();
                ret = isHold();
                ret = isEnd();
            }

        private:



             /*
            * 函数功能：均值归一化
            * 参数说明：
            * 			input: 输入特征集
            * 			output: 输出特征集
            *
            * 返回值：标准化 MFCC 集全局特征标准化,即归一化均值为0，方差为1
            * */
            void __cmn(std::vector<double> &input,std::vector<double> &output)
            {
                double sum = std::accumulate(input.begin(),input.end(), 0.0);
                double mean = sum / input.size();

                sum = 0;

                for(int i=0;i<input.size();i++)
                {
                    sum += (mean-input[i])*(mean-input[i]);
                }
                sum = sum/input.size();

                double xita = std::sqrt(sum);

                for(int i=0;i<input.size();i++)
                {
                    output[i] = (input[i]-mean)/xita;
                }
            }

            /*
            函数功能：计算MFCC L2 范数
            */
            double __caculateMfccL2()
            {
                double l2 = 0;
                for(auto item:m_mfcc)
                {
                    l2+=(item*item);
                }
                return log10(std::sqrt(l2));
            }

        private:
            vector<double> m_mfcc;
            MFCC_STATE m_state;
            double m_l2,m_low_threshold,m_up_threshold;
            double m_low_cfg,m_up_cfg;
            double m_noise_level,m_noise_frames;
            size_t m_holdtime_cfg,m_holdcount;
            deque<double> m_background_noise;
            bool m_is_noise_update;

    };
}



#endif