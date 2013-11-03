/*!
 *  \file       mco-core_Twang.h
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

#include "mco-core.h"
#include "engine/mco-core_Pitch.h"
#include "modules/mco-core_LFO.h"
#include "modules/mco-core_Envelope.h"

BEGIN_MCO_CORE_NAMESPACE

template<class Traits>
class Twang
{
public:
    inline  Twang();
    inline ~Twang();

public:
    inline void init();

public:
    inline void process(Pitch& ioPitch);
    inline void process(ModSample& ioSample);
    inline void trigger();

public: // Oscillation parameters
    inline void setFrequency(Frequency inFreq);
    inline void setWaveform(byte inWaveform);

public: // Envelope parameters
    inline void setDecay(DecayEnvelope::Decay inDecay);
    inline void setLinearity(DecayEnvelope::LinearityAmount inAmount);

private:
    typedef typename Traits::LfoMapper LfoFreqMapper;
    typedef LFO<LfoFreqMapper> Lfo;
    Lfo mLfo;
    DecayEnvelope mEnvelope;
};

END_MCO_CORE_NAMESPACE

#include "modules/mco-core_Twang.hpp"
