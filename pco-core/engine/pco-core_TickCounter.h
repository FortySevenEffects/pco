#pragma once

#include "pco-core.h"
#include <interrupts/ak47_Atomic.h>

BEGIN_PCO_CORE_NAMESPACE

class TickCounter
{
public:
    typedef uint16 TickCount;

public:
    inline  TickCounter();
    inline ~TickCounter();

public:
    inline void tick();
    inline void fetchTickCounter(TickCount& outCount);
    inline void resetTickCounter();

private:
    volatile TickCount mCount;
};

END_PCO_CORE_NAMESPACE

#include "engine/pco-core_TickCounter.hpp"
