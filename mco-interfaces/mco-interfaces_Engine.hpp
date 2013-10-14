/*!
 *  \file       mco-firmware_Engine.hpp
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

BEGIN_MCO_FIRMWARE_NAMESPACE

inline Engine::Engine()
    : mEngine()
    , mModulation()
    , mSpi(mEngine, mModulation)
{
}

inline Engine::~Engine()
{
}

// -----------------------------------------------------------------------------

inline void Engine::init()
{
    mSpi.init();
    mEngine.init();
}

inline void Engine::process()
{
    mSpi.read();
    mEngine.process();
}

// -----------------------------------------------------------------------------

inline void TimerTraits::TimerOutput::init()
{
    //MCO_CLOCK_DDR |= (1 << MCO_CLOCK_PIN);  // Set output pin   
}

inline void TimerTraits::TimerOutput::startPulse()
{
/*
#if MCO_CLOCK_POLARITY
    MCO_CLOCK_PORT |= (1 << MCO_CLOCK_PIN);     // Pulse to VCC
#else
    MCO_CLOCK_PORT &= ~(1 << MCO_CLOCK_PIN);    // Pulse to GND
#endif
    */
}

inline void TimerTraits::TimerOutput::endPulse()
{
/*
#if MCO_CLOCK_POLARITY
    MCO_CLOCK_PORT &= ~(1 << MCO_CLOCK_PIN);    // Idle state: GND
#else
    MCO_CLOCK_PORT |= (1 << MCO_CLOCK_PIN);     // Idle state: VCC
#endif
    */
}

END_MCO_FIRMWARE_NAMESPACE
