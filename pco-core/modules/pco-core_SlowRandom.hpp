#pragma once

BEGIN_PCO_CORE_NAMESPACE

inline SlowRandom::SlowRandom()
{
}

inline SlowRandom::~SlowRandom()
{
}

// -----------------------------------------------------------------------------

inline void SlowRandom::process(Pitch& ioPitch)
{
    const Filter::Sample sample = rand() & 0x07;
    mFilter.samples[mFilter.writeIndex++] = sample;
    mFilter.writeIndex &= (Filter::Size - 1);

    int16 sum = 0;
    for (byte i = 0; i < Filter::Size; ++i)
    {
        sum += mFilter.samples[i];
    }
    sum >>= Filter::Shift;

    ioPitch.cents += sum;
    ioPitch.computeRange();
}

END_PCO_CORE_NAMESPACE
