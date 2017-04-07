#pragma once

BEGIN_PCO_CORE_NAMESPACE

template<class Timer>
PWM<Timer>::PWM(Timer& inTimer)
    : mTimer(inTimer)
{
}

template<class Timer>
PWM<Timer>::~PWM()
{
}

// -----------------------------------------------------------------------------

template<class Timer>
inline void PWM<Timer>::init()
{
    // mAmount = 0;         // Already init'd to zero at boot time.
    mLFO.init();
}

template<class Timer>
inline void PWM<Timer>::process()
{
    if (mAmount != 0)
    {
        ModSample sample = 0;
        mLFO.process(sample);
        int32 amount = (int32(sample) * int32(mAmount)) >> (sAmountShift + 1);
        mTimer.setPulseWidth(amount);
    }
}

template<class Timer>
inline void PWM<Timer>::tick()
{
    mLFO.tick();
}

// -----------------------------------------------------------------------------

template<class Timer>
inline void PWM<Timer>::setBaseLevel(RelativeLevel inLevel)
{
    mBaseLevel = inLevel;
}

template<class Timer>
inline void PWM<Timer>::setAmount(Amount inAmount)
{
    mAmount = inAmount;
}

template<class Timer>
inline void PWM<Timer>::setSpeed(Frequency inSpeed)
{
    mLFO.setFrequency(inSpeed);
}

template<class Timer>
inline void PWM<Timer>::setWaveform(byte inWaveform)
{
    mLFO.setWaveform(inWaveform);
}

END_PCO_CORE_NAMESPACE
