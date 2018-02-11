/*
 * ConfigResolver.h
 *
 *  Created on: 2016年12月28日
 *      Author: hntea
 */

#ifndef _CONFIGRESOLVER_H_
#define _CONFIGRESOLVER_H_

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <vector>
#include <algorithm>
#include "xfparams.h"

namespace Hntea {
using namespace std;
class ConfigResolver {
public:
ConfigResolver(){};
	ConfigResolver(std::string file);
	virtual ~ConfigResolver();
	void process();
	void setCfgfile(std::string file);
	
	XfBasic getXfBasic();
	XfOnlineASR getXfOnlineParams();
	XfLocalASR getXfLocalParams();
	XfWakeupParams getXfWakeupParams();
private:
	XfBasic _basic;
	XfOnlineASR _online;
	XfLocalASR _local;
	XfWakeupParams _wakeup;
	std::string _file;
};

} /* namespace Hntea */

#endif /* SRC_ASR_SERVER_LIB_CONFIGRESOLVER_H_ */
