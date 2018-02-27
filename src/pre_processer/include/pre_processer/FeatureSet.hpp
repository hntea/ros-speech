#ifndef _FEATURESET_HPP
#define _FEATURESET_HPP

/*
 * FeatureSet.cpp
 *
 *  Created on: 2017年2月27日
 *      Author: hntea
 */

#include <iostream>
#include <vector>
#include <numeric>
#include "aquila/global.h"
#include "aquila/source/SignalSource.h"
#include "aquila/transform/Mfcc.h"
using namespace Aquila;
using namespace std;
namespace Hntea
{

class FeatureSet:public Aquila::SignalSource
{
public:
        FeatureSet(){};
        FeatureSet(const std::vector<SampleType>& data,
                     FrequencyType sampleFrequency=16000):SignalSource(data,sampleFrequency){};
        


        void setFreq(FrequencyType freq)
        {
            m_sampleFrequency=freq;
        }
        void setData(vector<SampleType>& data)
        {
            m_data = data;
        }

        /*
        短时能量
        */
        double getEnergy(){
            float energy = 0.0;

            for(auto item:m_data)
                energy+=(item*item);

            return 10*log10(energy);
        }

                
        /*
        * 函数功能：统计过零率
        * 参数说明：
        * 返回值：过零率
        * */
        float getZeroCrossing(){

            float prev = 0.0;
            float ret = 0.0;

            std::vector<double>::iterator iter = m_data.begin();

            for(int i=0;i<m_data.size();i++)
            {
                bool crossing = false;

                float sample = iter[i];

                if(sample >= 0.0)
                {
                    if(prev <0.0)
                        crossing = true;

                }else if(sample < 0.0)
                {
                    if(prev>=0.0)
                        crossing = true;
                }
                if(crossing == true)
                {
                    ret++;
                }
                prev = sample;
            }

            return ret;
        }



        /*
        * 函数功能：MFCC 全局特征标准化
        * 参数说明：
        * 			input: 输入特征集
        * 			output: 输出特征集
        *
        * 返回值：标准化 MFCC 集全局特征标准化,即归一化均值为0，方差为1
        * */
        void mfccCMN(const std::vector<double> &input,std::vector<double> &output)
        {
            double sum = std::accumulate(std::begin(input), std::end(input), 0.0);
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
        * 函数功能：获取MFCC特征集
        * 参数说明：
        * 			mfccValues: 特征集存放空间
        * 			numFeatures:特征序列个数
        * 返回值：MFCC集
        * */
        std::vector<double> getMfcc(std::size_t nums)
        {
            std::vector<double> ret(nums);
            Aquila::Mfcc mfcc(m_data.size());
            Aquila::SignalSource signal(m_data,m_sampleFrequency);
            ret = mfcc.calculate(signal,nums);
            return ret;
        }

        
};

}

#endif