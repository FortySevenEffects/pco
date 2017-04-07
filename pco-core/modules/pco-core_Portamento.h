#pragma once

#include "pco-core.h"
#include "engine/pco-core_Math.h"
#include "engine/pco-core_Pitch.h"
#include "engine/pco-core_FlagBox.h"
#include "engine/pco-core_Tables.h"

BEGIN_PCO_CORE_NAMESPACE

class Portamento
{
public:
    enum
    {
        Linear      = 0,
        Exponential = 1,
    };

public:
    inline Portamento();
    inline ~Portamento();

public:
    inline void init();
    inline void trigger(const Pitch& inTarget);
    inline void process(Pitch& outPitch);

public:
    inline void tick();

public:
    inline void setAmount(Amount inAmount);
    inline void setMode(byte inMode);
    inline void setEnabled(bool inEnabled);

private:
    inline void processLinear(Pitch& outPitch);
    inline void processExponential(Pitch& outPitch);

private:
    typedef uint16 Phase;
    Phase mPhase;
    volatile Phase mPhaseCounter;
    Pitch mTargetPitch;
    Pitch mOriginPitch;
    uint8 mMode;
};

END_PCO_CORE_NAMESPACE

#include "modules/pco-core_Portamento.hpp"
