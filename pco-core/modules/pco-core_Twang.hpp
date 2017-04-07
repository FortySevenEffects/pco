#pragma once

BEGIN_PCO_CORE_NAMESPACE

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

END_PCO_CORE_NAMESPACE
