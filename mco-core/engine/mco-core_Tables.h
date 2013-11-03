/*!
 *  \file       mco-core_Tables.h
 *  \author     Francois Best
 *  \date       30/01/2013
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

#include "mco-core.h"
#include "mco-core_Defs.h"

BEGIN_MCO_CORE_NAMESPACE

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

END_MCO_CORE_NAMESPACE
