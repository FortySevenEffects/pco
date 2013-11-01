/*!
 *  \file       mco-core_Pitch.h
 *  \author     Francois Best
 *  \date       02/02/2013
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

struct Pitch
{
    typedef int8    Semitones;
    typedef int16   Cents;
    typedef uint16  FlatPitch;
    
    inline Pitch();
    inline Pitch(Semitones inSemitones, Cents inCents);
    inline ~Pitch();
    
    inline Pitch& operator=(const Pitch& inPitch);
    inline Pitch& operator+=(const Pitch& inPitch);
    inline Pitch& operator-=(const Pitch& inPitch);
    
    inline FlatPitch flatten() const;
    inline void computeRange();
    inline void limit();
    
    Semitones semitones;
    Cents cents;
};

inline Pitch operator+(const Pitch& inA, const Pitch& inB);
inline Pitch operator-(const Pitch& inA, const Pitch& inB);

END_MCO_CORE_NAMESPACE

#include "engine/mco-core_Pitch.hpp"
