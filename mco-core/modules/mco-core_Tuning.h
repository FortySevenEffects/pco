/*!
 *  \file       mco-core_Tuning.h
 *  \author     Francois Best
 *  \date       07/11/2013
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

BEGIN_MCO_CORE_NAMESPACE

class Tuning
{
public:
    inline  Tuning();
    inline ~Tuning();

public:
    inline void init();
    inline void process(Pitch& outPitch);
    inline void cycleMode();

private:
    enum Mode
    {
          sweepOctave = 0
        , sweepSemi
        , sweepCents

        , numModes
    };

    inline void processSweepOctave();
    inline void processSweepSemi();
    inline void processSweepCents();

private:
    Pitch mCurrentPitch;
    byte mMode;
    uint32 mCounter;
};

END_MCO_CORE_NAMESPACE

#include "modules/mco-core_Tuning.hpp"
