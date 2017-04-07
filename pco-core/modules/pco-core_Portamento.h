/*!
 *  \file       pco-core_Portamento.h
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

#include "pco-core.h"
#include "engine/pco-core_Math.h"
#include "engine/pco-core_Pitch.h"
#include "engine/pco-core_FlagBox.h"
#include "engine/pco-core_Tables.h"

BEGIN_PCO_CORE_NAMESPACE

class Portamento
{
public:
    enum
    {
        Linear      = 0,
        Exponential = 1,
    };

public:
    inline Portamento();
    inline ~Portamento();

public:
    inline void init();
    inline void trigger(const Pitch& inTarget);
    inline void process(Pitch& outPitch);

public:
    inline void tick();

public:
    inline void setAmount(Amount inAmount);
    inline void setMode(byte inMode);
    inline void setEnabled(bool inEnabled);

private:
    inline void processLinear(Pitch& outPitch);
    inline void processExponential(Pitch& outPitch);

private:
    typedef uint16 Phase;
    Phase mPhase;
    volatile Phase mPhaseCounter;
    Pitch mTargetPitch;
    Pitch mOriginPitch;
    uint8 mMode;
};

END_PCO_CORE_NAMESPACE

#include "modules/pco-core_Portamento.hpp"
