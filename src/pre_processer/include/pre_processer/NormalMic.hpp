#ifndef _NORMALMIC_HPP
#define _NORMALMIC_HPP

/*
说明：单声道麦克风数据录入
*/

#include <iostream>
#include <assert.h>
#include <alsa/asoundlib.h>
#include "BDeviceParam.hpp"

using namespace std;
namespace Hntea{
class NormalMic
{
public:
	bool set_param(BDeviceParam* param);
	
	//单通道读取
	template <typename T>
	void read( T* buf,size_t size);

	//多通道读取
	template <typename T>
	void readn( T** buf,size_t size);

private:
	_snd_pcm_access m_access;		//数据存放方式
	_snd_pcm* m_handle;				//回话语句柄
};


bool NormalMic::set_param(BDeviceParam* param){

    assert(param != NULL);
	//配置
	int i;
	int err;
	snd_pcm_hw_params_t *hw_params;

	switch(param->mode)
	{
	case 0:
		if ((err = snd_pcm_open (&m_handle, param->name.c_str(), SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
			fprintf (stderr, "cannot open audio device %s (%s)\n",param->name.c_str(),snd_strerror (err));
			exit (1);
		}
				break;
	case 1:
		if ((err = snd_pcm_open (&m_handle,param->name.c_str(), SND_PCM_STREAM_CAPTURE, 0)) < 0) {
			fprintf (stderr, "cannot open audio device %s (%s)\n",param->name.c_str(),snd_strerror (err));
			exit (1);
		}
				break;
	default:
		if ((err = snd_pcm_open (&m_handle, param->name.c_str(), SND_PCM_STREAM_CAPTURE, 0)) < 0) {
			fprintf (stderr, "cannot open audio device %s (%s)\n",param->name.c_str(),snd_strerror (err));
			exit (1);
		}
				break;

	}

	//申请硬件参数配置空间
	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
		fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
		snd_strerror (err));
		exit (1);
	}

	//填充参数空间
	if ((err = snd_pcm_hw_params_any (m_handle, hw_params)) < 0) {
		fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
		snd_strerror (err));
		exit (1);
	}

	//配置处理模式 SND_PCM_ACCESS_RW_NONINTERLEAVED==非交错模式-多通道处理
	if ((err = snd_pcm_hw_params_set_access (m_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		fprintf (stderr, "cannot set access type (%s)\n",
		snd_strerror (err));
		exit (1);
	}

	//配置样本值,默认为16位
	switch(param->depth)
	{
		case 8:
			if ((err = snd_pcm_hw_params_set_format (m_handle, hw_params, SND_PCM_FORMAT_U8 )) < 0) {
				fprintf (stderr, "cannot set sample format (%s)\n",
				snd_strerror (err));
				exit (1);
			}
			break;
		case 16:
			if ((err = snd_pcm_hw_params_set_format (m_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
				fprintf (stderr, "cannot set sample format (%s)\n",
				snd_strerror (err));
				exit (1);
			}
			break;
		default:
			if ((err = snd_pcm_hw_params_set_format (m_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
				fprintf (stderr, "cannot set sample format (%s)\n",
				snd_strerror (err));
				exit (1);
			}
			break;
	}

	//配置采样频率
	if ((err = snd_pcm_hw_params_set_rate_near (m_handle, hw_params, &param->freq, 0)) < 0) {
		fprintf (stderr, "cannot set sample rate (%s)\n",
		snd_strerror (err));
		exit (1);
	}

	//配置通道数
	if ((err = snd_pcm_hw_params_set_channels (m_handle, hw_params, param->channels)) < 0) {
		fprintf (stderr, "cannot set channel count (%s)\n",
		snd_strerror (err));
		exit (1);
	}

	//写入参数
	if ((err = snd_pcm_hw_params (m_handle, hw_params)) < 0) {
		fprintf (stderr, "cannot set parameters (%s)\n",
		snd_strerror (err));
		exit (1);
	}

	//释放参数空间
	snd_pcm_hw_params_free (hw_params);

	if ((err = snd_pcm_prepare (m_handle)) < 0) {
		fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
		snd_strerror (err));
		exit (1);
	}
    return true;

}


//单通道读取
template <typename T>
void  NormalMic::read( T* buf,size_t size)
{
	int err = 0;
	assert(buf!=NULL);
	if ((err = snd_pcm_readi (m_handle,buf,size))
			!= size)
	{
		fprintf (stderr, "read from audio interface failed (%s)\n",
		snd_strerror (err));
		exit (1);
	}
}

//多通道读取
template <typename T>
void  NormalMic::readn( T** buf,size_t size)
{
	int err = 0;
	if ((err = snd_pcm_readn(m_handle,(void**)buf,size)) != size)
	{
		fprintf (stderr, "read from audio interface failed (%s)\n",
		snd_strerror (err));
		exit (1);
	}
}


}
#endif