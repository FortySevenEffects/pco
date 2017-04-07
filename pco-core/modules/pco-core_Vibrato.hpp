#pragma once

BEGIN_PCO_CORE_NAMESPACE

inline Vibrato::Vibrato()
{
}

inline Vibrato::~Vibrato()
{
}

// -----------------------------------------------------------------------------

inline void Vibrato::init()
{
    // mAmount = 0;         // Already init'd to zero at boot time.
    mLFO.init();
}

inline void Vibrato::process(Pitch& ioPitch)
{
    if (mAmount != 0)
    {
        ModSample sample = 0;
        mLFO.process(sample);
        int32 amount = (int32(sample) * int32(mAmount)) >> (sAmountShift + 1);
        ioPitch.cents += amount;
        ioPitch.computeRange();
    }
}

inline void Vibrato::reset()
{
    mLFO.reset();
}

inline void Vibrato::tick()
{
    mLFO.tick();
}

// -----------------------------------------------------------------------------

inline void Vibrato::setAmount(Amount inAmount)
{
    mAmount = inAmount;
}

inline void Vibrato::setSpeed(Frequency inSpeed)
{
    mLFO.setFrequency(inSpeed);
}

inline void Vibrato::setWaveform(byte inWaveform)
{
    mLFO.setWaveform(inWaveform);
}

END_PCO_CORE_NAMESPACE
