/*!
 *  \file       mco-core_Math.hpp
 *  \author     Francois Best
 *  \date       12/02/2013
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

inline uint14 decode_u14(uint7 inMSB, uint7 inLSB)
{
    return (inMSB << 7) | inLSB;
}

inline int14 decode_s14(uint7 inMSB, uint7 inLSB)
{
    // int16 pre-encoded
    //  42  0x002a
    // -42  0xffd6
    // 1242 0x04da
    //-1242 0xfb26
    
    // int14 pre-encoded
    //  42  0x002a  xx00 0000 0010 1010
    // -42  0x3fd6  xx11 1111 1101 0110
    // 1242 0x04da  xx00 0100 1101 1010
    //-1242 0x3b26  xx11 1011 0010 0110
    
    // int14 encoded      v--(sign)
    //  42  0x00 0x2a   x[00 0000 0] x[010 1010]
    // -42  0x7f 0x56   x[11 1111 1] x[101 0110]
    // 1242 0x09 0x5a   x[00 0100 1] x[101 1010]
    //-1242 0x76 0x26   x[11 1011 0] x[010 0110]
    
    if (inMSB & 0x40)
    {
        // Even though the value is on 14 bits, we still need to sign it on 16.
        return int14(0xC000 | uint16(inMSB << 7) | inLSB); 
    }
    else
    {
        // Positive side
        return (inMSB << 7) | inLSB; 
    }
}

// -----------------------------------------------------------------------------

inline int16 interpol_s(int16 inA, int16 inB, uint7 inAmount)
{
    const uint32 amountA = uint32(0x7f - inAmount) * uint32(inA);
    const uint32 amountB = uint32(inAmount) * uint32(inB);
    return (amountA + amountB) >> 7;
}

inline uint16 interpol_u(uint16 inA, uint16 inB, uint7 inAmount)
{
    const uint32 amountA = uint32(0x7f - inAmount) * uint32(inA);
    const uint32 amountB = uint32(inAmount) * uint32(inB);
    return (amountA + amountB) >> 7;
}

// -----------------------------------------------------------------------------

inline uint16 amount(uint16 inValue, Amount inAmount)
{
    return (uint32(inValue) * uint32(inAmount)) >> sAmountShift;
}

END_MCO_CORE_NAMESPACE
