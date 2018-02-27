#ifndef _HANMINGWIN_
#define _HANMINGWIN_

#include <aquila/source/window/HammingWindow.h>
#include <aquila/global.h>

using namespace Aquila;
namespace Hntea{
    class HanMingWin:public Aquila::HammingWindow
    {
        public:
            HanMingWin(size_t len):HammingWindow(len){}
     
            void addWindow(vector<SampleType>& source)
            {
                for(int i=0;i<m_data.size();i++)
                    source[i] = m_data[i]*source[i];
            }
    };
}

#endif