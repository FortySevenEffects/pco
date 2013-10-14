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

template<class TimerTraits>
inline Engine<TimerTraits>::Engine()
    : mTimer()
    , mPWM(mTimer)
{
}

template<class TimerTraits>
inline Engine<TimerTraits>::~Engine()
{
}

// -----------------------------------------------------------------------------

template<class TimerTraits>
inline void Engine<TimerTraits>::init()
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
    
    // Activate tick for modules
    TickTimer::enableInterruptOverflow();
    TickTimer::start(TickTimer::prescale1);

    sei(); // Activate global interrupts
}

template<class TimerTraits>
inline void Engine<TimerTraits>::process()
{
    mPortamento.process(mPitch);
    
    mPWM.process();

    Pitch modulation = mModulation;
    mVibrato.process(modulation);
    
    mPitch += modulation;
    mPitch += mDetune;
    computeClock();
}

template<class TimerTraits>
inline void Engine<TimerTraits>::setPitch(const Pitch& inPitch)
{
    mPortamento.trigger(inPitch);
    unmute();
}

template<class TimerTraits>
inline void Engine<TimerTraits>::setModulation(const Pitch& inPitch)
{
    mModulation = inPitch;
}

template<class TimerTraits>
inline void Engine<TimerTraits>::setDetune(const Pitch& inDetune)
{
    mDetune = inDetune;
}

template<class TimerTraits>
inline void Engine<TimerTraits>::handleSyncPulse()
{
    mTimer.reset();
}

// -----------------------------------------------------------------------------

template<class TimerTraits>
inline void Engine<TimerTraits>::mute()
{
    mTimer.stop();
}

template<class TimerTraits>
inline void Engine<TimerTraits>::unmute()
{
    mTimer.start();
}

// -----------------------------------------------------------------------------

template<class TimerTraits>
inline byte Engine<TimerTraits>::getCurrentOctave() const
{
    return mOctave;
}

template<class TimerTraits>
inline byte Engine<TimerTraits>::getCurrentSemiIndex() const
{
    return mSemiIndex;
}

template<class TimerTraits>
inline byte Engine<TimerTraits>::getCurrentCentsOffset() const
{
    return byte(mPitch.cents);
}

// -----------------------------------------------------------------------------

template<class TimerTraits>
inline void Engine<TimerTraits>::computeClock()
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

template<class TimerTraits>
inline void Engine<TimerTraits>::handleSyncTimerTick()
{
    mVibrato.tick();
    mPWM.tick();
    mPortamento.tick();
}

END_MCO_CORE_NAMESPACE
