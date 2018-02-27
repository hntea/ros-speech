#ifndef _PREEMPHASIS_HPP
#define _PREEMPHASIS_HPP

#include <iostream>
#include <vector>
using namespace std;

namespace Hntea
{
    class PreEmphasis{
	public:
    /*
	 * 函数功能：一阶滤波器 H(Z) = 1-uZ^{-1}
	 * 离散卷积响应表示：
	 * 			y[n] = x[n] - ux[n-1]
	 * */
    template<typename T>
	void preEmphasis(vector<T>& des,vector<T>& src,float u=0.98){
		for(int i=0;i<des.size();i++){
			if(i==0){
				des[i] = src[i];
			}else{
				des[i] = src[i] - src[i-1] * u;
			}
		}
	}
    };
}

#endif