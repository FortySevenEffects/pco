/*!
 *  \file       mco-core_Timer.hpp
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

template<class TimerInterface, class OutputInterface>
inline Timer<TimerInterface, OutputInterface>::Timer()
{
}

template<class TimerInterface, class OutputInterface>
inline Timer<TimerInterface, OutputInterface>::~Timer()
{
}

// -----------------------------------------------------------------------------

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::init()
{
    mValue = 0x800;
    mPrescale = TimerInterface::prescale8;

    OutputInterface::init();
    TimerInterface::template setMode<4>();  // CTC on A, no PWM
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::start()
{
    TimerInterface::enableInterruptA();     // A: start pulse
    TimerInterface::enableInterruptB();     // B: end pulse
    mRefresh = true;
    recomputeFrequency();
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::stop()
{
    TimerInterface::disableInterruptA();
    TimerInterface::disableInterruptB();
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::setTime(byte inPrescale,
                                                            uint16 inValue)
{
    mPrescale = inPrescale;
    mValue    = inValue;
    mRefresh  = true;
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::setPulseWidth(PulseWidth inPulseWidth)
{
    mPulseWidth = inPulseWidth;
    mRefresh    = true;
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::recomputeFrequency()
{
    if (mRefresh)
    {
        TimerInterface::setA(mValue);
        setPulseEnd(); 
        TimerInterface::setPrescale(mPrescale);
        mRefresh = false;
    }
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::reset()
{
    TimerInterface::stop();
    startPulse();
    TimerInterface::reset();
    mRefresh = true;
    recomputeFrequency();
}

// -----------------------------------------------------------------------------

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::handleInterruptA()
{
    startPulse();
    recomputeFrequency();
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::handleInterruptB()
{
    endPulse();
}

// -----------------------------------------------------------------------------

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::startPulse()
{
    OutputInterface::startPulse();
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::endPulse()
{
    OutputInterface::endPulse();
}

// -----------------------------------------------------------------------------

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::setPulseEnd()
{
    const int16 offset = (int32(mPulseWidth) * int32(mValue)) >> sPulseWidthShift;
    const uint16 baseValue = mValue >> 1; // Centred around 50%
    const uint16 pulseEndValue = baseValue + offset;
    TimerInterface::setB(pulseEndValue);
}

END_MCO_CORE_NAMESPACE
