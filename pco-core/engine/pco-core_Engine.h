#pragma once

#include "pco-core.h"
#include "engine/pco-core_Pitch.h"
#include "engine/pco-core_Timer.h"
#include "engine/pco-core_Tables.h"
#include "modules/pco-core_Portamento.h"
#include "modules/pco-core_Vibrato.h"
#include "modules/pco-core_PWM.h"
#include "modules/pco-core_SlowRandom.h"
#include "modules/pco-core_Tuning.h"
#include "modules/pco-core_Twang.h"
#include <avr/interrupt.h>

BEGIN_PCO_CORE_NAMESPACE

template<class Traits>
class Engine
{
public:
    typedef typename Traits::MainTimer      MainTimer;
    typedef typename Traits::TickTimer      TickTimer;
    typedef typename Traits::TimerOutput    TimerOutput;
    typedef Timer<MainTimer, TimerOutput>   TimerClass;
    typedef PWM<TimerClass>                 PwmClass;

public:
    inline  Engine();
    inline ~Engine();

public:
    inline void init();
    inline void process();

public:
    inline void setPitch(const Pitch& inPitch);
    inline void setModulation(const Pitch& inModulation);
    inline void setDetune(const Pitch& inDetune);
    inline void handleSyncPulse();

public:
    inline void mute();
    inline void unmute();

public:
    inline void setTuning(bool inTuning);

public:
    inline byte getCurrentOctave() const;
    inline byte getCurrentSemiIndex() const;
    inline byte getCurrentCentsOffset() const;

private:
    inline void computeClock();

public:
    inline void handleSystemTick();

public: // For convenience access
    TimerClass      mTimer;
    Tuning          mTuningModule;

    Portamento      mPortamento;
    Vibrato         mVibrato;
    PwmClass        mPWM;
    SlowRandom      mSlowRandom;

    struct TwangTraits
    {
        typedef ExpMapper<FixedPointTime, 1000, 4000000>    EnvelopeMapper;
        typedef ExpMapper<FixedPointFreq, 100, 10000>       LfoMapper;
    };
    Twang<TwangTraits> mTwang;

private:
    Pitch           mPitch;
    Pitch           mModulation;
    Pitch           mDetune;
    uint8           mOctave;
    uint8           mSemiIndex;
    uint8           mPrescaleIndex;
    uint32          mPrescaledClock;
    uint64          mClockDivision;
    bool            mTuning;
};

END_PCO_CORE_NAMESPACE

#include "engine/pco-core_Engine.hpp"
