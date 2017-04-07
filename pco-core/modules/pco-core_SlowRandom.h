#pragma once

#include "pco-core.h"
#include "engine/pco-core_Pitch.h"
#include <stdlib.h>

BEGIN_PCO_CORE_NAMESPACE

class SlowRandom
{
public:
    inline  SlowRandom();
    inline ~SlowRandom();

public:
    inline void init();
    inline void process(Pitch& ioPitch);

private:
    struct Filter
    {
        typedef int8 Sample;
        static const byte Shift = 4;
        static const byte Size  = (1 << Shift);

        Sample samples[Size];
        byte writeIndex;
    };

    Filter mFilter;
};

END_PCO_CORE_NAMESPACE

#include "modules/pco-core_SlowRandom.hpp"
