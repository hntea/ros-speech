#ifndef _BVAD_HPP
#define _BVAD_HPP

namespace Hntea
{
    enum MFCC_STATE
    {
        QUIET,
        MAYBE_START,
        START,
        HOLD,
        MAYBE_END,
        END,        
    };

    class Bvad
    {
    public:
        virtual bool isStart() = 0;
        virtual bool isEnd()=0;
        virtual bool isHold()=0;
        virtual bool isQuiet()=0;
    };
}

#endif