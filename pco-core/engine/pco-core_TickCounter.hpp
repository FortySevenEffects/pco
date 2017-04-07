#pragma once

BEGIN_PCO_CORE_NAMESPACE

inline TickCounter::TickCounter()
{
}

inline TickCounter::~TickCounter()
{
}

// -----------------------------------------------------------------------------

inline void TickCounter::tick()
{
    mCount++;
}

inline void TickCounter::fetchTickCounter(TickCount& outCount)
{
    cake::ScopedInterruptLock lock;
    outCount = mCount;
    mCount = 0;
}

inline void TickCounter::resetTickCounter()
{
    cake::ScopedInterruptLock lock;
    mCount = 0;
}

END_PCO_CORE_NAMESPACE
