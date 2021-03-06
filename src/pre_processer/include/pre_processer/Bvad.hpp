#ifndef _BVAD_HPP
#define _BVAD_HPP

namespace Hntea
{
    enum MFCC_STATE
    {
        QUIET,              //0
        MAYBE_START,        //1  
        START,              //2
        HOLD,               //3
        MAYBE_END,          //4
        END,                //5
    };

    class Bvad
    {
    public:
        virtual bool isStart() = 0;
        virtual bool isEnd()=0;
        virtual bool isHold()=0;
        virtual bool isQuiet()=0;
        void runvad()
        {
                bool ret;
                ret = isQuiet();
                ret = isStart();
                ret = isHold();
                ret = isEnd();
        }
    };
}

#endif