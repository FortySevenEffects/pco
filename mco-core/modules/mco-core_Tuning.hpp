/*!
 *  \file       mco-core_Tuning.hpp
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

BEGIN_MCO_CORE_NAMESPACE

inline Tuning::Tuning()
{
}

inline Tuning::~Tuning()
{
}

// -----------------------------------------------------------------------------

inline void Tuning::init()
{
}

inline void Tuning::process(Pitch& outPitch)
{
    switch (mMode)
    {
        case sweepOctave:   processSweepOctave();   break;
        case sweepSemi:     processSweepSemi();     break;
        case sweepCents:    processSweepCents();    break;
    }

    mCurrentPitch.limit();
    outPitch = mCurrentPitch;
}

inline void Tuning::cycleMode()
{
    mMode = (mMode + 1) % numModes;
    mCurrentPitch.semitones = 0;
    mCurrentPitch.cents = 0;
}

// -----------------------------------------------------------------------------

inline void Tuning::processSweepOctave()
{
    if (mCounter++ == 0)
    {
        mCurrentPitch.semitones += 12;    
    }
}

inline void Tuning::processSweepSemi()
{
    if (mCounter++ == 0)
    {
        mCurrentPitch.semitones++;
    }
}

inline void Tuning::processSweepCents()
{
    mCurrentPitch.cents++;
    mCurrentPitch.computeRange();
}

END_MCO_CORE_NAMESPACE
