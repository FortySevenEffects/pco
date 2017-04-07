/*!
 *  \file       pco-interfaces_Slope.h
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

#include "pco-interfaces.h"
#include <engine/pco-core_Pitch.h>

BEGIN_PCO_INTERFACES_NAMESPACE

class Slope
{
public:
    inline  Slope();
    inline ~Slope();

public:
    inline void init();
    inline void setValue(uint64 inClockDivision);
    inline void setValue(uint8 inOctave,
                         uint8 inSemiIndex,
                         uint8 inCents);

private:
    inline void internalSetValue(uint16 inValue);
};

END_PCO_INTERFACES_NAMESPACE

#include "interfaces/pco-interfaces_Slope.hpp"
