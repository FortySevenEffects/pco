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
/*
class AdsrEnvelope : public TickCounter
{
public:
    typedef UModSample  Sample;
    typedef uint14      TimeFactor;
    typedef TimeFactor  Attack;
    typedef TimeFactor  Decay;
    typedef TimeFactor  Release;
    typedef Sample      Sustain;

    enum // States
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
    inline void gateOn();
    inline void gateOff();

public:
    inline void setAttack(Attack inAttack);
    inline void setDecay(Decay inDecay);
    inline void setSustain(Sustain inLevel);
    inline void setRelease(Release inRelease);

private:
    inline bool updatePhase();
    inline void processAttack(Sample& outSample);
    inline void processDecay(Sample& outSample);
    inline void processSustain(Sample& outSample);
    inline void processRelease(Sample& outSample);

private:
    Sustain mSustainLevel;

    byte mState;
    Sample mCurrentValue;

    Phase mPhase;
    Phase mCurrentPhaseIncrement;
};
*/
// -----------------------------------------------------------------------------

class DecayEnvelope : public TickCounter
{
public:
    typedef UModSample  Sample;
    typedef uint14      TimeFactor;
    typedef TimeFactor  Decay;
    typedef byte        LinearityAmount;

public:
    inline  DecayEnvelope();
    inline ~DecayEnvelope();

public:
    inline void init();
    inline void process(Sample& outSample);
    inline void trigger();
    inline void setDecay(Decay inDecay);
    inline void setLinearity(LinearityAmount inAmount);

public:
    inline bool isActive() const;

private:
    inline bool updatePhase();
    inline Sample processLinear() const;
    inline Sample processExponential() const;

private:
    bool mProcessing;
    Phase mPhase;
    Phase mPhaseIncrement;
    LinearityAmount mLinearity;
};

END_MCO_CORE_NAMESPACE

#include "modules/mco-core_Envelope.hpp"
