/*!
 *  \file       pco-core_Vibrato.hpp
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

BEGIN_PCO_CORE_NAMESPACE

inline Vibrato::Vibrato()
{
}

inline Vibrato::~Vibrato()
{
}

// -----------------------------------------------------------------------------

inline void Vibrato::init()
{
    // mAmount = 0;         // Already init'd to zero at boot time.
    mLFO.init();
}

inline void Vibrato::process(Pitch& ioPitch)
{
    if (mAmount != 0)
    {
        ModSample sample = 0;
        mLFO.process(sample);
        int32 amount = (int32(sample) * int32(mAmount)) >> (sAmountShift + 1);
        ioPitch.cents += amount;
        ioPitch.computeRange();
    }
}

inline void Vibrato::reset()
{
    mLFO.reset();
}

inline void Vibrato::tick()
{
    mLFO.tick();
}

// -----------------------------------------------------------------------------

inline void Vibrato::setAmount(Amount inAmount)
{
    mAmount = inAmount;
}

inline void Vibrato::setSpeed(Frequency inSpeed)
{
    mLFO.setFrequency(inSpeed);
}

inline void Vibrato::setWaveform(byte inWaveform)
{
    mLFO.setWaveform(inWaveform);
}

END_PCO_CORE_NAMESPACE
