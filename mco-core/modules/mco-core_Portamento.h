/*!
 *  \file       mco-core_Portamento.h
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
#include "engine/mco-core_Pitch.h"
#include "modules/mco-core_Envelope.h"

BEGIN_MCO_CORE_NAMESPACE

class Portamento
{
public:
    typedef DecayEnvelope               Envelope;
    typedef Envelope::LinearityAmount   LinearityAmount;
    typedef Envelope::TimeFactor        TimeFactor;

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
    inline void setDuration(TimeFactor inDuration);
    inline void setLinearity(LinearityAmount inAmount);

private:
    Envelope mEnvelope;

    Pitch mTargetPitch;
    Pitch mOriginPitch;
    uint8 mMode;
};

END_MCO_CORE_NAMESPACE

#include "modules/mco-core_Portamento.hpp"
