#pragma once

BEGIN_PCO_CORE_NAMESPACE

template<class Mapper>
inline DecayEnvelope<Mapper>::DecayEnvelope()
{
}

template<class Mapper>
inline DecayEnvelope<Mapper>::~DecayEnvelope()
{
}

// -----------------------------------------------------------------------------

template<class Mapper>
inline void DecayEnvelope<Mapper>::init()
{
}

template<class Mapper>
inline void DecayEnvelope<Mapper>::process(Sample& outSample)
{
    if (mProcessing)
    {
        Sample sampleLin = 0;
        Sample sampleExp = 0;
        processLinear(sampleLin);
        processExponential(sampleExp);

        // Blend
        outSample = interpol_u(sampleLin, sampleExp, mBendAmount);

        if (updatePhase())
        {
            // Phase overflow: reached the end of decay time.
            mProcessing = false;
        }
    }
}

template<class Mapper>
inline void DecayEnvelope<Mapper>::trigger()
{
    mProcessing = true;
    mPhase = 0;
    resetTickCounter();
}

template<class Mapper>
inline void DecayEnvelope<Mapper>::setDuration(TimeFactor inDuration)
{
    setPhaseIncrement(computePhaseIncrement(inDuration));
}

template<class Mapper>
inline void DecayEnvelope<Mapper>::setBend(BendAmount inAmount)
{
    mBendAmount = inAmount;
}

// -----------------------------------------------------------------------------

template<class Mapper>
inline bool DecayEnvelope<Mapper>::isActive() const
{
    return mProcessing;
}

// -----------------------------------------------------------------------------

template<class Mapper>
inline Phase DecayEnvelope<Mapper>::computePhaseIncrement(TimeFactor inTime)
{
    static const Phase phaseMax = 0xffff;
    static const FixedPointTime tickTime = 1000000 / sTickFrequency; // 12
    const FixedPointTime time = Mapper::map(inTime);    // min: 1000, max = 4000000
    const uint16 numTicksPerPeriod = time / tickTime;   // min: 83,   max = 333333 -> overflow
    return phaseMax / numTicksPerPeriod;
}

template<class Mapper>
inline void DecayEnvelope<Mapper>::setPhaseIncrement(Phase inIncrement)
{
    mPhaseIncrement = inIncrement;
}

template<class Mapper>
inline bool DecayEnvelope<Mapper>::updatePhase()
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

template<class Mapper>
inline void DecayEnvelope<Mapper>::processLinear(Sample& outSample)
{
    outSample = sUModSampleMax - mPhase;
}

template<class Mapper>
inline void DecayEnvelope<Mapper>::processExponential(Sample& outSample)
{
    const uint7 index = (mPhase >> 9);          // index range: [0 ; 127]
    const uint7 alpha = (mPhase >> 2) & 0x7f;   // alpha range: [0 ; 127]
    const uint16 expA = LookupTables::getExpDischarge(index + 1);
    const uint16 expB = LookupTables::getExpDischarge(index);
    outSample = interpol_u(expA, expB, alpha);
}

// ########################################################################## //

template<class Mapper>
inline AdsrEnvelope<Mapper>::AdsrEnvelope()
{
}

template<class Mapper>
inline AdsrEnvelope<Mapper>::~AdsrEnvelope()
{
}

// -----------------------------------------------------------------------------

template<class Mapper>
inline void AdsrEnvelope<Mapper>::init()
{
    mCore.init();
    setAttack(0);
    setDecay(0);
    setSustain(sUModSampleMax);
    setRelease(0);
}

template<class Mapper>
inline void AdsrEnvelope<Mapper>::process(Sample& outSample)
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
    mPreviousSample = outSample;
}

template<class Mapper>
inline void AdsrEnvelope<Mapper>::tick()
{
    mCore.tick();
}

// -----------------------------------------------------------------------------

template<class Mapper>
inline void AdsrEnvelope<Mapper>::gateOn()
{
    mState = idle;
    changeState();
}

template<class Mapper>
inline void AdsrEnvelope<Mapper>::gateOff()
{
    mState = sustain;
    changeState();
}

// -----------------------------------------------------------------------------

template<class Mapper>
inline void AdsrEnvelope<Mapper>::setAttack(TimeFactor inAttack)
{
    mAttackPhaseIncr = CoreEnvelope::computePhaseIncrement(inAttack);
    if (mState == attack)
    {
        mCore.setPhaseIncrement(mAttackPhaseIncr);
    }
}

template<class Mapper>
inline void AdsrEnvelope<Mapper>::setDecay(TimeFactor inDecay)
{
    mDecayPhaseIncr = CoreEnvelope::computePhaseIncrement(inDecay);
    if (mState == decay)
    {
        mCore.setPhaseIncrement(mDecayPhaseIncr);
    }
}

template<class Mapper>
inline void AdsrEnvelope<Mapper>::setSustain(Sample inLevel)
{
    mSustainLevel = inLevel;
}

template<class Mapper>
inline void AdsrEnvelope<Mapper>::setRelease(TimeFactor inRelease)
{
    mReleasePhaseIncr = CoreEnvelope::computePhaseIncrement(inRelease);
    if (mState == release)
    {
        mCore.setPhaseIncrement(mReleasePhaseIncr);
    }
}

template<class Mapper>
inline void AdsrEnvelope<Mapper>::setBend(BendAmount inAmount)
{
    mCore.setBend(inAmount);
}

// -----------------------------------------------------------------------------

template<class Mapper>
inline void AdsrEnvelope<Mapper>::changeState()
{
    switch (mState)
    {
        case idle:
        {
            mState = attack;
            mCore.setPhaseIncrement(mAttackPhaseIncr);
            mCore.trigger();
            break;
        }

        case attack:
        {
            mState = decay;
            mCore.setPhaseIncrement(mDecayPhaseIncr);
            mCore.trigger();
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
            mCore.setPhaseIncrement(mReleasePhaseIncr);
            mCore.trigger();
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

template<class Mapper>
inline void AdsrEnvelope<Mapper>::processAttack(Sample& outSample)
{
    Sample sample = 0;
    mCore.process(sample);
    outSample = sUModSampleMax - sample;
}

template<class Mapper>
inline void AdsrEnvelope<Mapper>::processDecay(Sample& outSample)
{
    Sample sample = 0;
    mCore.process(sample);

    const uint32 scale = sUModSampleMax - mSustainLevel;
    const Sample scaledSample = scale * uint32(sample) >> 16;
    outSample = mSustainLevel + scaledSample;
}

template<class Mapper>
inline void AdsrEnvelope<Mapper>::processSustain(Sample& outSample)
{
    outSample = mSustainLevel;
}

template<class Mapper>
inline void AdsrEnvelope<Mapper>::processRelease(Sample& outSample)
{
    Sample sample = 0;
    mCore.process(sample);

    const uint32 scale = sUModSampleMax - mSustainLevel;
    const Sample scaledSample = scale * uint32(sample) >> 16;
    outSample = mSustainLevel + scaledSample;
}

END_PCO_CORE_NAMESPACE
