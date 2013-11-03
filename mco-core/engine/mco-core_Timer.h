/*!
 *  \file       mco-core_Timer.h
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
#include "mco-core_Defs.h"
#include "engine/mco-core_Math.h"
#include <time/ak47_Timer.h>

BEGIN_MCO_CORE_NAMESPACE

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
    volatile bool mRefresh;
};

END_MCO_CORE_NAMESPACE

#include "engine/mco-core_Timer.hpp"
