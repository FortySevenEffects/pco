/*!
 *  \file       mco-core_Mappers.hpp
 *  \author     Francois Best
 *  \date       27/10/2013
 *  \license    GPL v3.0 - Copyright Forty Seven Effects 2013
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

BEGIN_MCO_CORE_NAMESPACE

template<typename Type, Type Min, Type Max>
inline Type LinMapper<Type, Min, Max>::map(Amount inAmount)
{
    return Min + ((uint32(Max - Min) * uint32(inAmount)) >> sAmountShift);
}

template<typename Type, Type Min, Type Max, uint7 BendAmount>
inline Type ExpMapper<Type, Min, Max, BendAmount>::map(Amount inAmount)
{
    const Type valueLin     = LinMapper<Type, Min, Max>::map(inAmount);
    const Amount revAmount  = sAmountMax - inAmount; // Discharge to rising exp
    const byte index        = revAmount >> 7;
    const byte alpha        = revAmount & 0x7f;
    const uint16 expA       = LookupTables::getExpDischarge(index);
    const uint16 expB       = LookupTables::getExpDischarge(index + 1);
    const uint16 amountExp  = interpol_u(expA, expB, alpha);
    const Type valueExp     = LinMapper<Type, Min, Max>::map(amountExp >> 2);

    const uint32 amountA = uint32(0x7f - BendAmount) * uint32(valueLin);
    const uint32 amountB = uint32(BendAmount) * uint32(valueExp);
    return (amountA + amountB) >> 7;
}

template<typename Type, Type Min, Type Max, uint7 BendAmount>
inline Type LogMapper<Type, Min, Max, BendAmount>::map(Amount inAmount)
{
    const Type valueLin = LinMapper<Type, Min, Max>::map(inAmount);
    const byte index        = inAmount >> 7;
    const byte alpha        = inAmount & 0x7f;
    const uint16 logA       = LookupTables::getExpDischarge(index);
    const uint16 logB       = LookupTables::getExpDischarge(index + 1);
    const uint16 amountLog  = 0xffff - interpol_u(logA, logB, alpha); // Discharge to rising log
    const Type valueLog     = LinMapper<Type, Min, Max>::map(amountLog >> 2);

    const uint32 amountA = uint32(0x7f - BendAmount) * uint32(valueLin);
    const uint32 amountB = uint32(BendAmount) * uint32(valueLog);
    return (amountA + amountB) >> 7;
}

END_MCO_CORE_NAMESPACE
