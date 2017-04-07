#pragma once

BEGIN_PCO_CORE_NAMESPACE

template<typename Type, Type Min, Type Max>
inline Type LinearMapper<Type, Min, Max>::map(Amount inAmount)
{
    return Min + ((uint32(Max - Min) * uint32(inAmount)) >> sAmountShift);
}

END_PCO_CORE_NAMESPACE
