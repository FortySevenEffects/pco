#pragma once

#include "pco-core.h"
#include "engine/pco-core_Math.h"
#include "engine/pco-core_Mappers.h"
#include "modules/pco-core_LFO.h"

BEGIN_PCO_CORE_NAMESPACE

template<class Timer>
class PWM
{
public:
    typedef int14 RelativeLevel;

public:
    inline  PWM(Timer& inTimer);
    inline ~PWM();

public:
    inline void init();
    inline void process();
    inline void tick();

public:
    inline void setBaseLevel(RelativeLevel inLevel);
    inline void setAmount(Amount inAmount);
    inline void setSpeed(Frequency inSpeed);
    inline void setWaveform(byte inWaveform);

private:
    typedef LinMapper<FixedPointFreq, 1000, 8000> SpeedMapper;
    typedef LFO<SpeedMapper> PwmLfo;

    Timer& mTimer;
    RelativeLevel mBaseLevel;
    Amount mAmount;
    PwmLfo mLFO;
};

END_PCO_CORE_NAMESPACE

#include "modules/pco-core_PWM.hpp"
