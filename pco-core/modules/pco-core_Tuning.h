#pragma once

#include "pco-core.h"
#include "engine/pco-core_Pitch.h"

BEGIN_PCO_CORE_NAMESPACE

class Tuning
{
public:
    inline  Tuning();
    inline ~Tuning();

public:
    inline void init();
    inline void process(Pitch& outPitch);
    inline void cycleMode();

private:
    enum Mode
    {
          sweepOctave = 0
        , sweepSemi
        , sweepCents

        , numModes
    };

    inline void processSweepOctave();
    inline void processSweepSemi();
    inline void processSweepCents();

private:
    Pitch mCurrentPitch;
    byte mMode;
    uint32 mCounter;
};

END_PCO_CORE_NAMESPACE

#include "modules/pco-core_Tuning.hpp"
