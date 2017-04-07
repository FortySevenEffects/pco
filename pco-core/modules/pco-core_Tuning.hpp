#pragma once

BEGIN_PCO_CORE_NAMESPACE

inline Tuning::Tuning()
{
}

inline Tuning::~Tuning()
{
}

// -----------------------------------------------------------------------------

inline void Tuning::init()
{
}

inline void Tuning::process(Pitch& outPitch)
{
    switch (mMode)
    {
        case sweepOctave:   processSweepOctave();   break;
        case sweepSemi:     processSweepSemi();     break;
        case sweepCents:    processSweepCents();    break;
    }

    mCurrentPitch.limit();
    outPitch = mCurrentPitch;
}

inline void Tuning::cycleMode()
{
    mMode = (mMode + 1) % numModes;
    mCurrentPitch.semitones = 0;
    mCurrentPitch.cents = 0;
}

// -----------------------------------------------------------------------------

inline void Tuning::processSweepOctave()
{
    if (mCounter++ == 0)
    {
        mCurrentPitch.semitones += 12;
    }
}

inline void Tuning::processSweepSemi()
{
    if (mCounter++ == 0)
    {
        mCurrentPitch.semitones++;
    }
}

inline void Tuning::processSweepCents()
{
    mCurrentPitch.cents++;
    mCurrentPitch.computeRange();
}

END_PCO_CORE_NAMESPACE
