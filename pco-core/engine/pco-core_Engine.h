#pragma once

#include "pco-core.h"
#include "engine/pco-core_Pitch.h"
#include "engine/pco-core_Timer.h"
#include "engine/pco-core_Tables.h"
#include "engine/pco-core_FlagBox.h"
#include "modules/pco-core_Portamento.h"
#include "modules/pco-core_Vibrato.h"
#include "modules/pco-core_PWM.h"
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
    inline byte getCurrentOctave() const;
    inline byte getCurrentSemiIndex() const;
    inline byte getCurrentCentsOffset() const;

private:
    inline void computeClock();

public:
    inline void handleSystemTick();

public: // For convenience access
    TimerClass      mTimer;
    Portamento      mPortamento;
    Vibrato         mVibrato;
    PwmClass        mPWM;

private:
    Pitch           mPitch;
    Pitch           mModulation;
    Pitch           mDetune;
    uint8           mOctave;
    uint8           mSemiIndex;
    uint8           mPrescaleIndex;
    uint32          mPrescaledClock;
    uint64          mClockDivision;
};

END_PCO_CORE_NAMESPACE

#include "engine/pco-core_Engine.hpp"
