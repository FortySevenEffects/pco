/*!
 *  \file       pco-core_LFO.h
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

#include "pco-core.h"
#include "pco-core_Defs.h"
#include "engine/pco-core_TickCounter.h"
#include "engine/pco-core_Math.h"
#include "engine/pco-core_Tables.h"
#include <avr/io.h>

BEGIN_PCO_CORE_NAMESPACE

template<class Mapper>
class LFO : public TickCounter
{
public:
    enum
    {
        Sine        = 0,
        Square      = 1,
        Saw         = 2,
        Ramp        = 3,
        Triangle    = 4,

        numWaveforms
    };

public:
    inline  LFO();
    inline ~LFO();

public:
    inline void init();
    inline void process(ModSample& outSample);
    inline void reset();

public:
    inline void setFrequency(Frequency inFrequency);
    inline void setWaveform(byte inWaveform);

private:
    inline void generateSine(ModSample& outSample);
    inline void generateSquare(ModSample& outSample);
    inline void generateSaw(ModSample& outSample);
    inline void generateRamp(ModSample& outSample);
    inline void generateTriangle(ModSample& outSample);

private:
    inline void updatePhase();

private:
    Phase mPhase;
    Phase mPhaseIncrement;
    byte mWaveform;
};

END_PCO_CORE_NAMESPACE

#include "modules/pco-core_LFO.hpp"
