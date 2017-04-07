#pragma once

#include "pco-core.h"
#include "pco-core_Defs.h"
#include "engine/pco-core_Math.h"
#include "engine/pco-core_FlagBox.h"
#include <time/cake_Timer.h>

BEGIN_PCO_CORE_NAMESPACE

template<class TimerInterface, class OutputInterface>
class Timer
{
public:
    inline  Timer();
    inline ~Timer();

public:
    inline void init();
    inline void start();
    inline void stop();
    inline void setTime(byte inPrescale, uint16 inValue);
    inline void setPulseWidth(PulseWidth inPulseWidth);
    inline void recomputeFrequency();
    inline void reset();

public:
    inline void handleInterruptA();
    inline void handleInterruptB();

private:
    inline void startPulse();
    inline void endPulse();

private:
    inline void setPulseEnd();

private:
    volatile uint16 mValue;
    volatile byte mPrescale;
    volatile PulseWidth mPulseWidth;
};

END_PCO_CORE_NAMESPACE

#include "engine/pco-core_Timer.hpp"
