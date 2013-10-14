/*!
 *  \file       mco-core_Pitch.hpp
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

BEGIN_MCO_CORE_NAMESPACE

inline Pitch::Pitch()
    : semitones(0)
    , cents(0)
{
}

inline Pitch::Pitch(Semitones inSemitones, Cents inCents)
    : semitones(inSemitones)
    , cents(inCents)
{
    computeRange();
}

inline Pitch::~Pitch()
{
}

// -----------------------------------------------------------------------------

inline Pitch& Pitch::operator=(const Pitch& inPitch)
{
    semitones = inPitch.semitones;
    cents = inPitch.cents;
    computeRange();
    return *this;
}

inline Pitch& Pitch::operator+=(const Pitch& inPitch)
{
    semitones += inPitch.semitones;
    cents += inPitch.cents;
    computeRange();
    return *this;
}

// -----------------------------------------------------------------------------

inline Pitch::FlatPitch Pitch::flatten() const
{
    // Here we assume the pitch is positive (not to be used on modulation)
    return semitones * 100 + cents;
}

inline void Pitch::computeRange()
{
    while (cents >= 100)
    {
        semitones++;
        cents -= 100;
    }
    while (cents < 0)
    {
        semitones--;
        cents += 100;
    }
}

inline void Pitch::limit()
{
    if (semitones < 0)
    {
        semitones = 0;
    }
}

END_MCO_CORE_NAMESPACE
