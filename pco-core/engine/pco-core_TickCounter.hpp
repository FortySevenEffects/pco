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
    ak47::ScopedInterruptLock lock;
    outCount = mCount;
    mCount = 0;
}

inline void TickCounter::resetTickCounter()
{
    ak47::ScopedInterruptLock lock;
    mCount = 0;
}

END_PCO_CORE_NAMESPACE
