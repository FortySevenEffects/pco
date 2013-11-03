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
/*
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
    setSustain(sUModSampleMax);
    setRelease(0);
}

inline void AdsrEnvelope::process(Sample& outSample)
{
    const bool overflow = updatePhase();
    if (overflow)
    {
        // go to next state
    }

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

inline void AdsrEnvelope::setAttack(Attack inAttack)
{
    // \todo Compute time constant and phase incr here.
}

inline void AdsrEnvelope::setDecay(Decay inDecay)
{
    // \todo Compute time constant and phase incr here.
}

inline void AdsrEnvelope::setSustain(Sustain inLevel)
{
    mSustainLevel = inSustain;
}

inline void AdsrEnvelope::setRelease(Release inRelease)
{
    // \todo Compute time constant and phase incr here.
}

// -----------------------------------------------------------------------------

inline bool AdsrEnvelope::updatePhase()
{
    TickCount ticks = 0;
    fetchTickCounter(ticks);
    const Phase increment = ticks * mPhaseIncrement;
    if (increment > (0xffff - mPhase))
    {
        // Increment will overflow
        mPhase = 0;
        return true;
    }

    mPhase += increment;
    return false;
}

inline void AdsrEnvelope::processAttack(Sample& outSample)
{
    if (mCurrentValue == sUModSampleMax)
    {
        mState = decay;
        processDecay(outSample);
        return;
    }

    return mPhase; // Linear output
}

inline void AdsrEnvelope::processDecay(Sample& outSample)
{

}

inline void AdsrEnvelope::processSustain(Sample& outSample)
{
    mCurrentValue = mSustainLevel;
    outSample = mCurrentValue;
}

inline void AdsrEnvelope::processRelease(Sample& outSample)
{
    if (mCurrentValue == 0)
    {
        mState = idle;
        return;
    }

    // \todo Implement me.
}
*/

// ########################################################################## //

inline DecayEnvelope::DecayEnvelope()
{
}

inline DecayEnvelope::~DecayEnvelope()
{
}

// -----------------------------------------------------------------------------

inline void DecayEnvelope::init()
{
}

inline void DecayEnvelope::process(Sample& outSample)
{
    if (mProcessing)
    {
        if (updatePhase())
        {
            // Phase overflow: reached the end of decay time.
            mProcessing = false;
            return;
        }

        const Sample sampleLin = processLinear();
        const Sample sampleExp = processExponential();

        // Blend
        outSample = interpol_s(sampleExp, sampleLin, mLinearity);
    }
}

inline void DecayEnvelope::trigger()
{
    mProcessing = true;
    mPhase = 0;
    resetTickCounter();
}

inline void DecayEnvelope::setDecay(Decay inDecay)
{
    mPhaseIncrement = 0xffff - inDecay;
}

inline void DecayEnvelope::setLinearity(LinearityAmount inAmount)
{
    mLinearity = inAmount;
}

// -----------------------------------------------------------------------------

inline bool DecayEnvelope::isActive() const
{
    return mProcessing;
}

// -----------------------------------------------------------------------------

inline bool DecayEnvelope::updatePhase()
{
    TickCount ticks = 0;
    fetchTickCounter(ticks);
    const uint32 increment = ticks * mPhaseIncrement;
    if (increment > uint32(0xffff - mPhase))
    {
        // Increment will overflow
        mPhase = 0;
        return true;
    }

    mPhase += increment;
    return false;
}

inline DecayEnvelope::Sample DecayEnvelope::processLinear() const
{
    return sUModSampleMax - mPhase;
}

inline DecayEnvelope::Sample DecayEnvelope::processExponential() const
{
    const uint7 index = (mPhase >> 9);          // index range: [0 ; 127]
    const uint7 alpha = (mPhase >> 2) & 0x7f;   // alpha range: [0 ; 127]
    const uint16 expA = LookupTables::getExpDischarge(index + 1);
    const uint16 expB = LookupTables::getExpDischarge(index);
    return interpol_u(expA, expB, alpha);
}

END_MCO_CORE_NAMESPACE
