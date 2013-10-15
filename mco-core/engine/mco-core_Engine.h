/*!
 *  \file       mco-core_Engine.h
 *  \author     Francois Best
 *  \date       30/01/2013
 *  \license    GPL v3.0 - Copyright Forty Seven Effects 2013
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "mco-core.h"
#include "engine/mco-core_Pitch.h"
#include "engine/mco-core_Timer.h"
#include "engine/mco-core_Tables.h"
#include "engine/mco-core_FlagBox.h"
#include "modules/mco-core_Portamento.h"
#include "modules/mco-core_Vibrato.h"
#include "modules/mco-core_PWM.h"
#include <avr/interrupt.h>

BEGIN_MCO_CORE_NAMESPACE

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
    inline void handleSyncTimerTick();

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

END_MCO_CORE_NAMESPACE

#include "engine/mco-core_Engine.hpp"
