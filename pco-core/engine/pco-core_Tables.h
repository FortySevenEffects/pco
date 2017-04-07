#pragma once

#include "pco-core.h"
#include "pco-core_Defs.h"

BEGIN_PCO_CORE_NAMESPACE

struct LookupTables
{
    static uint16 getCentInterpolation(byte inIndex);
    static uint32 getClockDivision(byte inNote);
    static byte   getPrescaleShift(byte inIndex);
    static int16  getHalfSine(byte inIndex);
    static uint16 getLog(byte inIndex);
    static uint16 getExpDischarge(byte inIndex);
    static uint16 getSlope(byte inIndex);
};

END_PCO_CORE_NAMESPACE
