#pragma once

#include "pco-core.h"
#include "engine/pco-core_Math.h"
#include "engine/pco-core_Pitch.h"
#include "engine/pco-core_Mappers.h"
#include "modules/pco-core_LFO.h"

BEGIN_PCO_CORE_NAMESPACE

class Vibrato
{
public:
    inline  Vibrato();
    inline ~Vibrato();

public:
    inline void init();
    inline void process(Pitch& ioPitch);
    inline void reset();
    inline void tick();

public:
    inline void setAmount(Amount inAmount);
    inline void setSpeed(Frequency inSpeed);
    inline void setWaveform(byte inWaveform);

private:
    typedef ExpMapper<FixedPointFreq, 1000, 8000> SpeedMapper;
    typedef LFO<SpeedMapper> VibratoLfo;

    Amount      mAmount;
    VibratoLfo  mLFO;
};

END_PCO_CORE_NAMESPACE

#include "modules/pco-core_Vibrato.hpp"
