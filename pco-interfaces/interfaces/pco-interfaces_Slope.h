#pragma once

#include "pco-interfaces.h"
#include <engine/pco-core_Pitch.h>

BEGIN_PCO_INTERFACES_NAMESPACE

class Slope
{
public:
    inline  Slope();
    inline ~Slope();

public:
    inline void init();
    inline void setValue(uint64 inClockDivision);
    inline void setValue(uint8 inOctave,
                         uint8 inSemiIndex,
                         uint8 inCents);

private:
    inline void internalSetValue(uint16 inValue);
};

END_PCO_INTERFACES_NAMESPACE

#include "interfaces/pco-interfaces_Slope.hpp"
