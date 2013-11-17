/*!
 *  \file       mco-core_Math.h
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

#include "mco-core.h"
#include "mco-core_Defs.h"

BEGIN_MCO_CORE_NAMESPACE

inline uint14 decode_u14(uint7 inMSB, uint7 inLSB);
inline int14  decode_s14(uint7 inMSB, uint7 inLSB);

// -----------------------------------------------------------------------------

inline int16 interpol_s(int16 inA, int16 inB, uint7 inAmount);
inline uint16 interpol_u(uint16 inA, uint16 inB, uint7 inAmount);

// -----------------------------------------------------------------------------

inline uint16 amount(uint16 inValue, Amount inAmount);
inline int16 amount(int16 inValue, Amount inAmount);

END_MCO_CORE_NAMESPACE

#include "engine/mco-core_Math.hpp"
