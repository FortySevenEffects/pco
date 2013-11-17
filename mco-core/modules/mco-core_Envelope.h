/*!
 *  \file       mco-core_Envelope.h
 *  \author     Francois Best
 *  \date       21/10/2013
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
#include "mco-core_Defs.h"
#include "engine/mco-core_TickCounter.h"
#include "engine/mco-core_Math.h"
#include "engine/mco-core_Tables.h"

BEGIN_MCO_CORE_NAMESPACE

template<class Mapper> class AdsrEnvelope;

template<class Mapper>
class DecayEnvelope
    : public TickCounter
{
public:
    typedef UModSample  Sample;
    typedef uint7       BendAmount; // 0: linear ; 0x7f: exponential

public:
    inline  DecayEnvelope();
    inline ~DecayEnvelope();

public:
    inline void init();
    inline void process(Sample& outSample);
    inline void trigger();
    inline void setDuration(TimeFactor inDuration);
    inline void setBend(BendAmount inAmount);

public:
    inline bool isActive() const;

private:
    static inline Phase computePhaseIncrement(TimeFactor inTime);
    inline void setPhaseIncrement(Phase inIncrement);

private:
    inline bool updatePhase();
    inline void processLinear(Sample& outSample);
    inline void processExponential(Sample& outSample);

private:
    bool mProcessing;
    Phase mPhase;
    Phase mPhaseIncrement;
    BendAmount mBendAmount;

private:
    friend class AdsrEnvelope<Mapper>;
};

// -----------------------------------------------------------------------------

template<class Mapper>
class AdsrEnvelope
{
public:
    typedef DecayEnvelope<Mapper>               CoreEnvelope;
    typedef typename CoreEnvelope::Sample       Sample;
    typedef typename CoreEnvelope::BendAmount   BendAmount;

    enum State
    {
          idle = 0
        , attack
        , decay
        , sustain
        , release
    };

public:
    inline  AdsrEnvelope();
    inline ~AdsrEnvelope();

public:
    inline void init();
    inline void process(Sample& outSample);
    inline void tick();

public:
    inline void gateOn();
    inline void gateOff();

public:
    inline void setAttack(TimeFactor inAttack);
    inline void setDecay(TimeFactor inDecay);
    inline void setSustain(Sample inLevel);
    inline void setRelease(TimeFactor inRelease);
    inline void setBend(BendAmount inAmount);

private:
    inline void changeState();
    inline void processAttack(Sample& outSample);
    inline void processDecay(Sample& outSample);
    inline void processSustain(Sample& outSample);
    inline void processRelease(Sample& outSample);

private:
    Phase mAttackPhaseIncr;
    Phase mDecayPhaseIncr;
    Sample mSustainLevel;
    Phase mReleasePhaseIncr;

    State mState;
    CoreEnvelope mCore;
    Sample mPreviousSample;
};

END_MCO_CORE_NAMESPACE

#include "modules/mco-core_Envelope.hpp"
