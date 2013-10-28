/*!
 *  \file       mco-core_TickCounter.h
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

#include "mco-core.h"
#include <interrupts/ak47_Atomic.h>

BEGIN_MCO_CORE_NAMESPACE

class TickCounter
{
public:
    typedef uint16 TickCount;

public:
    inline  TickCounter();
    inline ~TickCounter();

public:
    inline void tick();
    inline void fetchTickCounter(TickCount& outCount);
    inline void resetTickCounter();

private:
    volatile TickCount mCount;
};

END_MCO_CORE_NAMESPACE

#include "modules/mco-core_TickCounter.hpp"
