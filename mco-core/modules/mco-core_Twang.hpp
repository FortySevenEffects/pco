/*!
 *  \file       mco-core_Twang.hpp
 *  \author     Francois Best
 *  \date       03/11/2013
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
inline Twang<Traits>::Twang()
{
}

template<class Traits>
inline Twang<Traits>::~Twang()
{
}


// -----------------------------------------------------------------------------

template<class Traits>
inline void Twang<Traits>::init()
{
    mLfo.init();
    mEnvelope.init();
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void Twang<Traits>::process(Pitch& ioPitch)
{
    ModSample sample = 0;
    process(sample);
    ioPitch.cents += sample;
    ioPitch.computeRange();
}

template<class Traits>
inline void Twang<Traits>::process(ModSample& ioSample)
{
    if (mEnvelope.isActive() && mAmount)
    {
        ModSample  lfoSample = 0;
        UModSample envSample = 0;

        mLfo.process(lfoSample);
        mEnvelope.process(envSample);

        const ModSample fullScaleMod = (int32(lfoSample) * int32(envSample)) >> 16;
        ioSample += amount(fullScaleMod, mAmount);
    }
}

template<class Traits>
inline void Twang<Traits>::trigger()
{
    mLfo.reset();
    mEnvelope.trigger();
}

template<class Traits>
inline void Twang<Traits>::tick()
{
    mLfo.tick();
    mEnvelope.tick();
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void Twang<Traits>::setFrequency(Frequency inFreq)
{
    mLfo.setFrequency(inFreq);
}

template<class Traits>
inline void Twang<Traits>::setWaveform(byte inWaveform)
{
    mLfo.setWaveform(inWaveform);
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void Twang<Traits>::setDuration(TimeFactor inDuration)
{
    mEnvelope.setDuration(inDuration);
}

template<class Traits>
inline void Twang<Traits>::setBend(BendAmount inAmount)
{
    mEnvelope.setBend(inAmount);
}

template<class Traits>
inline void Twang<Traits>::setAmount(Amount inAmount)
{
    mAmount = inAmount;
}

END_MCO_CORE_NAMESPACE
