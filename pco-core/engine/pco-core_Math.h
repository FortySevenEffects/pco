#pragma once

#include "pco-core.h"
#include "pco-core_Defs.h"

BEGIN_PCO_CORE_NAMESPACE

inline uint14 decode_u14(uint7 inMSB, uint7 inLSB);
inline int14  decode_s14(uint7 inMSB, uint7 inLSB);

// -----------------------------------------------------------------------------

inline int16 interpol(int16 inA, int16 inB, uint7 inAmount);

// -----------------------------------------------------------------------------

inline uint16 amount(uint16 inValue, Amount inAmount);

END_PCO_CORE_NAMESPACE

#include "engine/pco-core_Math.hpp"
