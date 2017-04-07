#pragma once

BEGIN_PCO_CORE_NAMESPACE

template<class TimerInterface, class OutputInterface>
inline Timer<TimerInterface, OutputInterface>::Timer()
{
}

template<class TimerInterface, class OutputInterface>
inline Timer<TimerInterface, OutputInterface>::~Timer()
{
}

// -----------------------------------------------------------------------------

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::init()
{
    mValue = 0x800;
    mPrescale = TimerInterface::prescale8;

    OutputInterface::init();
    TimerInterface::template setMode<4>();  // CTC on A, no PWM
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::start()
{
    TimerInterface::enableInterruptA();     // A: start pulse
    TimerInterface::enableInterruptB();     // B: end pulse
    mRefresh = true;
    recomputeFrequency();
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::stop()
{
    TimerInterface::disableInterruptA();
    TimerInterface::disableInterruptB();
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::setTime(byte inPrescale,
                                                            uint16 inValue)
{
    mPrescale = inPrescale;
    mValue    = inValue;
    mRefresh  = true;
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::setPulseWidth(PulseWidth inPulseWidth)
{
    mPulseWidth = inPulseWidth;
    mRefresh    = true;
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::recomputeFrequency()
{
    if (mRefresh)
    {
        TimerInterface::setA(mValue);
        setPulseEnd();
        TimerInterface::setPrescale(mPrescale);
        mRefresh = false;
    }
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::reset()
{
    TimerInterface::stop();
    startPulse();
    TimerInterface::reset();
    mRefresh = true;
    recomputeFrequency();
}

// -----------------------------------------------------------------------------

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::handleInterruptA()
{
    startPulse();
    recomputeFrequency();
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::handleInterruptB()
{
    endPulse();
}

// -----------------------------------------------------------------------------

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::startPulse()
{
    OutputInterface::startPulse();
}

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::endPulse()
{
    OutputInterface::endPulse();
}

// -----------------------------------------------------------------------------

template<class TimerInterface, class OutputInterface>
inline void Timer<TimerInterface, OutputInterface>::setPulseEnd()
{
    const int16 offset = (int32(mPulseWidth) * int32(mValue)) >> sPulseWidthShift;
    const uint16 baseValue = mValue >> 1; // Centred around 50%
    const uint16 pulseEndValue = baseValue + offset;
    TimerInterface::setB(pulseEndValue);
}

END_PCO_CORE_NAMESPACE
