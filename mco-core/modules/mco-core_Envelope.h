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
#include "engine/mco-core_Math.h"
#include "engine/mco-core_Tables.h"

BEGIN_MCO_CORE_NAMESPACE

class AdsrEnvelope
{
public:
    typedef uint14 TimeFactor;
    typedef TimeFactor Attack;
    typedef TimeFactor Decay;
    typedef TimeFactor Release;
    typedef ModSample  Sustain;

    enum
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
    inline void process(ModSample& outSample);
    inline void gateOn();
    inline void gateOff();
    inline void tick();

public:
    inline void setAttack(Attack inAttack);
    inline void setDecay(Decay inDecay);
    inline void setSustain(Sustain inSustain);
    inline void setRelease(Release inRelease);

private:
    inline void processAttack(ModSample& outSample);
    inline void processDecay(ModSample& outSample);
    inline void processSustain(ModSample& outSample);
    inline void processRelease(ModSample& outSample);

private:
    volatile Phase mPhase;
    volatile Phase mPrescaleCounter;
    Phase mPrescaleThreshold;
    Phase mPhaseIncrement;
    Phase mBufferedPhase;

    Attack mAttack;
    Decay mDecay;
    Sustain mSustain;
    Release mRelease;

    byte mState;
    ModSample mCurrentValue;
};

END_MCO_CORE_NAMESPACE

#include "modules/mco-core_Envelope.hpp"
