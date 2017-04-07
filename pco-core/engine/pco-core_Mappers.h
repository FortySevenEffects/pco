#pragma once

#include "pco-core.h"
#include "pco-core_Defs.h"
#include "engine/pco-core_Math.h"
#include "engine/pco-core_Tables.h"

BEGIN_PCO_CORE_NAMESPACE

template<typename Type, Type Min, Type Max>
struct LinMapper
{
    static inline Type map(Amount inAmount);
};

template<typename Type, Type Min, Type Max, uint7 BendAmount = 0x7f>
struct ExpMapper
{
    static inline Type map(Amount inAmount);
};

template<typename Type, Type Min, Type Max, uint7 BendAmount = 0x7f>
struct LogMapper
{
    static inline Type map(Amount inAmount);
};

END_PCO_CORE_NAMESPACE

#include "engine/pco-core_Mappers.hpp"
