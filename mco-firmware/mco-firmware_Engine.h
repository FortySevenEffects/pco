/*!
 *  \file       mco-firmware_Engine.h
 *  \author     Francois Best
 *  \date       19/05/2013
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

#include "mco-firmware.h"
#include <engine/mco-core_Engine.h>
#include <interfaces/mco-core_SPI.h>
#include <interfaces/mco-core_Modulation.h>
#include <time/ak47_Timer.h>

BEGIN_MCO_FIRMWARE_NAMESPACE

struct TimerTraits
{
    typedef ak47::Timer1 MainTimer;
    typedef ak47::Timer0 TickTimer;

    struct TimerOutput
    {
        static inline void init();
        
        static inline void startPulse();
        static inline void endPulse();
    };
};

// -----------------------------------------------------------------------------

class Engine
{
public:
    typedef mco_core::Engine<TimerTraits>       McoEngine;
    typedef mco_core::SpiInterface<McoEngine>   McoSpi;
    typedef mco_core::ModulationInput           McoMod;

public:
    inline  Engine();
    inline ~Engine();

public:
    inline void init();
    inline void process();

private:
    McoEngine   mEngine;
    McoMod      mModulation;
    McoSpi      mSpi;
};

END_MCO_FIRMWARE_NAMESPACE

#include "mco-firmware_Engine.hpp"
