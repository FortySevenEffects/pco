/*!
 *  \file       mco-core_Envelope.hpp
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

BEGIN_MCO_CORE_NAMESPACE

inline AdsrEnvelope::AdsrEnvelope()
{
}

inline AdsrEnvelope::~AdsrEnvelope()
{
}

// -----------------------------------------------------------------------------

inline void AdsrEnvelope::init()
{
    setAttack(0);
    setDecay(0);
    setSustain(sModSampleMax);
    setRelease(0);
}

inline void AdsrEnvelope::process(ModSample& outSample)
{
    mBufferedPhase = mPhase;
    switch (mState)
    {
        default:
        case idle:
            break;

        case attack:    processAttack(outSample);   break;
        case decay:     processDecay(outSample);    break;
        case sustain:   processSustain(outSample);  break;
        case release:   processRelease(outSample);  break;
    }
}

// -----------------------------------------------------------------------------

inline void AdsrEnvelope::gateOn()
{
    mState = attack;
}

inline void AdsrEnvelope::gateOff()
{
    mState = release;
}

// -----------------------------------------------------------------------------

inline void AdsrEnvelope::tick()
{
    mPrescaleCounter++;
    if (mPrescaleCounter >= mPrescaleThreshold)
    {
        mPhase += mPhaseIncrement;
        mPrescaleCounter = 0;
    }
}

// -----------------------------------------------------------------------------

inline void AdsrEnvelope::setAttack(Attack inAttack)
{
    // \todo Compute time constant and phase incr here.
}

inline void AdsrEnvelope::setDecay(Decay inDecay)
{
    // \todo Compute time constant and phase incr here.
}

inline void AdsrEnvelope::setSustain(Sustain inSustain)
{
    mSustain = inSustain;
}

inline void AdsrEnvelope::setRelease(Release inRelease)
{
    // \todo Compute time constant and phase incr here.
}

// -----------------------------------------------------------------------------

inline void AdsrEnvelope::processAttack(ModSample& outSample)
{
    if (mCurrentValue == sModSampleMax)
    {
        mState = decay;
        processDecay(outSample);
        return;
    }

    // \todo Implement me.
}

inline void AdsrEnvelope::processDecay(ModSample& outSample)
{
    // \todo Implement me.
}

inline void AdsrEnvelope::processSustain(ModSample& outSample)
{
    mCurrentValue = mSustain;
    outSample = mCurrentValue;
}

inline void AdsrEnvelope::processRelease(ModSample& outSample)
{
    if (mCurrentValue == 0)
    {
        mState = idle;
        return;
    }

    // \todo Implement me.
}

END_MCO_CORE_NAMESPACE
