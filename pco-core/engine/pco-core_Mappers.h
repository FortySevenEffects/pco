#pragma once

#include "pco-core.h"
#include "pco-core_Defs.h"

BEGIN_PCO_CORE_NAMESPACE

template<typename Type, Type Min, Type Max>
struct LinearMapper
{
    static inline Type map(Amount inAmount);
};

END_PCO_CORE_NAMESPACE

#include "engine/pco-core_Mappers.hpp"
