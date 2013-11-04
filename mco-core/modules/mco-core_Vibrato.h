/*!
 *  \file       mco-core_Vibrato.h
 *  \author     Francois Best
 *  \date       11/02/2013
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
#include "engine/mco-core_Pitch.h"
#include "engine/mco-core_Mappers.h"
#include "modules/mco-core_LFO.h"

BEGIN_MCO_CORE_NAMESPACE

class Vibrato
{
public:
    inline  Vibrato();
    inline ~Vibrato();
    
public:
    inline void init();
    inline void process(Pitch& ioPitch);
    inline void reset();
    inline void tick();
    
public:
    inline void setAmount(Amount inAmount);
    inline void setSpeed(Frequency inSpeed);
    inline void setWaveform(byte inWaveform);
    
private:
    typedef ExpMapper<FixedPointFreq, 1000, 8000> SpeedMapper;
    typedef LFO<SpeedMapper> VibratoLfo;

    Amount      mAmount;
    VibratoLfo  mLFO;
};

END_MCO_CORE_NAMESPACE

#include "modules/mco-core_Vibrato.hpp"
