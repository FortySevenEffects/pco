/*!
 *  \file       mco-core_PWM.h
 *  \author     Francois Best
 *  \date       26/04/2013
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
#include "engine/mco-core_Math.h"
#include "engine/mco-core_FlagBox.h"
#include "modules/mco-core_LFO.h"

BEGIN_MCO_CORE_NAMESPACE

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
    Timer& mTimer;
    RelativeLevel mBaseLevel;
    Amount mAmount;
    LFO mLFO;
};

END_MCO_CORE_NAMESPACE

#include "modules/mco-core_PWM.hpp"
