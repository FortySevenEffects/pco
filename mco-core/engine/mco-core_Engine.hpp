/*!
 *  \file       mco-core_Engine.hpp
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

BEGIN_MCO_CORE_NAMESPACE

template<class Traits>
inline Engine<Traits>::Engine()
    : mTimer()
    , mPWM(mTimer)
{
}

template<class Traits>
inline Engine<Traits>::~Engine()
{
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void Engine<Traits>::init()
{
    // Set the CPU clock divider to 1 (full speed)
    CLKPR = 0x80;
    CLKPR = 0x00;
    
    // This is in case the fuses have not been set up correctly.
    // Set them with the following command:
    // avrdude -p t84   -U lfuse:w:0xef:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
    // avrdude -p m644p -U lfuse:w:0xef:m -U hfuse:w:0xdc:m -U efuse:w:0xfd:m
    // See this useful tool: http://www.engbedded.com/fusecalc/
    
    mTimer.init();
    mPortamento.init();
    mVibrato.init();
    mPWM.init();
    mTwang.init();

    // Activate tick for modules - Match defs in mco-core_Defs.h
    TickTimer::enableInterruptOverflow();
    TickTimer::start(TickTimer::prescale1);

    sei(); // Activate global interrupts

    mTwang.setDuration(1000);   // 1 second
    mTwang.setFrequency(1000);  // 1 Hz
    mTwang.setLinearity(0xff);  // Full linear
}

template<class Traits>
inline void Engine<Traits>::process()
{
    mPortamento.process(mPitch);
    
    mPWM.process();

    Pitch modulation = mModulation;
    mVibrato.process(modulation);
    mSlowRandom.process(modulation);
    
    mPitch += modulation;
    mPitch += mDetune;
    computeClock();
}

template<class Traits>
inline void Engine<Traits>::setPitch(const Pitch& inPitch)
{
    mPortamento.trigger(inPitch);
    mTwang.trigger();
    unmute();
}

template<class Traits>
inline void Engine<Traits>::setModulation(const Pitch& inPitch)
{
    mModulation = inPitch;
}

template<class Traits>
inline void Engine<Traits>::setDetune(const Pitch& inDetune)
{
    mDetune = inDetune;
}

template<class Traits>
inline void Engine<Traits>::handleSyncPulse()
{
    mTimer.reset();
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void Engine<Traits>::mute()
{
    mTimer.stop();
}

template<class Traits>
inline void Engine<Traits>::unmute()
{
    mTimer.start();
}

// -----------------------------------------------------------------------------

template<class Traits>
inline byte Engine<Traits>::getCurrentOctave() const
{
    return mOctave;
}

template<class Traits>
inline byte Engine<Traits>::getCurrentSemiIndex() const
{
    return mSemiIndex;
}

template<class Traits>
inline byte Engine<Traits>::getCurrentCentsOffset() const
{
    return byte(mPitch.cents);
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void Engine<Traits>::computeClock()
{
    mPitch.limit();                 // Constrain to acceptable range.
    mOctave = 0;
    mSemiIndex = mPitch.semitones;

    while (mSemiIndex >= 12)
    {
        mOctave++;
        mSemiIndex -= 12;
    }

    mClockDivision = LookupTables::getClockDivision(mSemiIndex) >> mOctave;
    
    if (mPitch.cents != 0)
    {
        mClockDivision *= LookupTables::getCentInterpolation(mPitch.cents - 1);
        mClockDivision >>= 16;
    }
    
    mPrescaleIndex = 1; // 1 because prescale = 0 means clock is stopped.
    mPrescaledClock = mClockDivision;
    
    while (mPrescaledClock > 0xffff)
    {
        mPrescaledClock = mClockDivision >> LookupTables::getPrescaleShift(mPrescaleIndex);
        mPrescaleIndex++;
    }
    
    mTimer.setTime(mPrescaleIndex, mPrescaledClock);
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void Engine<Traits>::handleSystemTick()
{
    mVibrato.tick();
    mPWM.tick();
    mPortamento.tick();
    mTwang.tick();
}

END_MCO_CORE_NAMESPACE
