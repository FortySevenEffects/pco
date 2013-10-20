/*!
 *  \file       mco-core_PWM.hpp
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

BEGIN_MCO_CORE_NAMESPACE

template<class Timer>
PWM<Timer>::PWM(Timer& inTimer)
    : mTimer(inTimer)
{
}

template<class Timer>
PWM<Timer>::~PWM()
{
}

// -----------------------------------------------------------------------------

template<class Timer>
inline void PWM<Timer>::init()
{
    // mAmount = 0;         // Already init'd to zero at boot time.
    mLFO.init();
}

template<class Timer>
inline void PWM<Timer>::process()
{
    ModSample sample = 0;
    mLFO.process(sample);
    int32 amount = (int32(sample) * int32(mAmount)) >> (sAmountShift + 1);
    mTimer.setPulseWidth(amount);
}

template<class Timer>
inline void PWM<Timer>::tick()
{
    mLFO.tick();
}

// -----------------------------------------------------------------------------

template<class Timer>
inline void PWM<Timer>::setBaseLevel(RelativeLevel inLevel)
{
    mBaseLevel = inLevel;
}

template<class Timer>
inline void PWM<Timer>::setAmount(Amount inAmount)
{
    mAmount = inAmount;
}

template<class Timer>
inline void PWM<Timer>::setSpeed(Frequency inSpeed)
{
    mLFO.setFrequency(inSpeed);
}

template<class Timer>
inline void PWM<Timer>::setWaveform(byte inWaveform)
{
    mLFO.setWaveform(inWaveform);
}

END_MCO_CORE_NAMESPACE
