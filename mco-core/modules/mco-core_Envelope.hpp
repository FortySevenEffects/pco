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
        const Sample sampleLin = processLinear();
        const Sample sampleExp = processExponential();

        // Blend
        outSample = interpol_s(sampleExp, sampleLin, mLinearity);

        if (updatePhase())
        {
            // Phase overflow: reached the end of decay time.
            mProcessing = false;
        }
    }
}

inline void DecayEnvelope::trigger()
{
    mProcessing = true;
    mPhase = 0;
    resetTickCounter();
}

inline void DecayEnvelope::setDuration(TimeFactor inDuration)
{
    mPhaseIncrement = 0xffff - inDuration;
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

// ########################################################################## //

inline AdsrEnvelope::AdsrEnvelope()
{
}

inline AdsrEnvelope::~AdsrEnvelope()
{
}

// -----------------------------------------------------------------------------

inline void AdsrEnvelope::init()
{
    mCore.init();
    setAttack(0);
    setDecay(0);
    setSustain(sUModSampleMax);
    setRelease(0);
}

inline void AdsrEnvelope::process(Sample& outSample)
{
    switch (mState)
    {
        case attack:
        case decay:
        case release:
            if (!mCore.isActive())
                changeState();
            break;
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

inline void AdsrEnvelope::tick()
{
    mCore.tick();
}

// -----------------------------------------------------------------------------

inline void AdsrEnvelope::gateOn()
{
    mState = idle;
    changeState();
}

inline void AdsrEnvelope::gateOff()
{
    mState = sustain;
    changeState();
}

// -----------------------------------------------------------------------------

inline void AdsrEnvelope::setAttack(TimeFactor inAttack)
{
    mAttackTime = inAttack;
    if (mState == attack)
    {
        mCore.setDuration(mAttackTime);
    }
}

inline void AdsrEnvelope::setDecay(TimeFactor inDecay)
{
    mDecayTime = inDecay;
    if (mState == decay)
    {
        mCore.setDuration(mDecayTime);
    }
}

inline void AdsrEnvelope::setSustain(Sample inLevel)
{
    mSustainLevel = inLevel;
}

inline void AdsrEnvelope::setRelease(TimeFactor inRelease)
{
    mReleaseTime = inRelease;
    if (mState == release)
    {
        mCore.setDuration(mReleaseTime);
    }
}

// -----------------------------------------------------------------------------

inline void AdsrEnvelope::changeState()
{
    switch (mState)
    {
        case idle:
        {
            mState = attack;
            if (mAttackTime == 0)
            {
                // go directly to decay
                changeState();
            }
            else
            {
                mCore.setDuration(mAttackTime);
                mCore.trigger();
            }
            break;
        }

        case attack:
        {
            mState = decay;
            if (mDecayTime == 0)
            {
                // go directly to sustain
                changeState();
            }
            else
            {
                mCore.setDuration(mDecayTime);
                mCore.trigger();
            }
            break;
        }

        case decay:
        {
            if (mSustainLevel == 0)
            {
                mState = idle;
            }
            else
            {
                mState = sustain;
            }
            break;
        }

        case sustain:
        {
            mState = release;
            if (mReleaseTime == 0)
            {
                // go directly to idle
                changeState();
            }
            else
            {
                mCore.setDuration(mReleaseTime);
                mCore.trigger();
            }
            break;
        }

        case release: // go to idle
        {
            mState = idle;
            break;
        }

        default:
            mState = idle;
            break;
    }
}

inline void AdsrEnvelope::processAttack(Sample& outSample)
{
    Sample sample = 0;
    mCore.process(sample);
    outSample = sUModSampleMax - sample;
}

inline void AdsrEnvelope::processDecay(Sample& outSample)
{
    Sample sample = 0;
    mCore.process(sample);

    const uint32 scale = sUModSampleMax - mSustainLevel;
    const Sample scaledSample = scale * uint32(sample) >> 16;
    outSample = mSustainLevel + scaledSample;
}

inline void AdsrEnvelope::processSustain(Sample& outSample)
{
    outSample = mSustainLevel;
}

inline void AdsrEnvelope::processRelease(Sample& outSample)
{
    Sample sample = 0;
    mCore.process(sample);

    const uint32 scale = sUModSampleMax - mSustainLevel;
    const Sample scaledSample = scale * uint32(sample) >> 16;
    outSample = mSustainLevel + scaledSample;
}

END_MCO_CORE_NAMESPACE
