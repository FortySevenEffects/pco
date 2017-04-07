#pragma once

BEGIN_PCO_CORE_NAMESPACE

template<class Mapper>
inline LFO<Mapper>::LFO()
{
}

template<class Mapper>
inline LFO<Mapper>::~LFO()
{
}

// -----------------------------------------------------------------------------

template<class Mapper>
inline void LFO<Mapper>::init()
{
    setFrequency(8000);
}

template<class Mapper>
inline void LFO<Mapper>::process(ModSample& outSample)
{
    updatePhase();
    switch (mWaveform)
    {
        case Sine:      generateSine(outSample);        break;
        case Square:    generateSquare(outSample);      break;
        case Saw:       generateSaw(outSample);         break;
        case Ramp:      generateRamp(outSample);        break;
        case Triangle:  generateTriangle(outSample);    break;
        default:
            break;
    }
}

template<class Mapper>
inline void LFO<Mapper>::reset()
{
    resetTickCounter();
    mPhase = 0;
}

// -----------------------------------------------------------------------------

template<class Mapper>
inline void LFO<Mapper>::setWaveform(byte inWaveform)
{
    mWaveform = inWaveform % numWaveforms;
}

template<class Mapper>
inline void LFO<Mapper>::setFrequency(Frequency inFrequency)
{
    static const Phase phaseMax = 0xffff;
    static const FixedPointFreq tickFreq = sTickFrequency * 1000;

    const FixedPointFreq freq = Mapper::map(inFrequency);
    const uint16 numTicksPerPeriod = tickFreq / freq;
    mPhaseIncrement = phaseMax / numTicksPerPeriod;
}

// -----------------------------------------------------------------------------

template<class Mapper>
inline void LFO<Mapper>::generateSine(ModSample& outSample)
{
    // 256 points for half wave -> 512 points for full wave
    // use overflow for index
    // Phase    0                     7fff 8000                  ffff
    // Sign     [ ++++++++++++++++++++++ ] [ ---------------------- ]
    // Index    0                      255 0                      255
    // Factor   1                        1 -1                      -1

    const uint8 index = mPhase >> 7;
    const uint7 alpha = mPhase & 0x7f;
    const int16 sampleA = LookupTables::getHalfSine(index);
    const int16 sampleB = LookupTables::getHalfSine(index + 1);
    const int16 sign = (mPhase & 0x8000) ? -1 : 1;
    outSample = sign * interpol_s(sampleA, sampleB, alpha);
}

template<class Mapper>
inline void LFO<Mapper>::generateSquare(ModSample& outSample)
{
    outSample = (mPhase & 0x8000) ? sModSampleMax : sModSampleMin;
}

template<class Mapper>
inline void LFO<Mapper>::generateSaw(ModSample& outSample)
{
    outSample = sModSampleMax - mPhase;
}

template<class Mapper>
inline void LFO<Mapper>::generateRamp(ModSample& outSample)
{
    outSample = sModSampleMin + mPhase;
}

template<class Mapper>
inline void LFO<Mapper>::generateTriangle(ModSample& outSample)
{
    outSample = (mPhase & 0x8000) ? sModSampleMax - (2 * (mPhase & 0x7fff))
                                  : sModSampleMin + 2 * mPhase;
}

// -----------------------------------------------------------------------------

template<class Mapper>
inline void LFO<Mapper>::updatePhase()
{
    TickCount ticks = 0;
    fetchTickCounter(ticks);
    mPhase += ticks * mPhaseIncrement;
}

END_PCO_CORE_NAMESPACE
