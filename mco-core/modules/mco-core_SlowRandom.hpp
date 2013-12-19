/*!
 *  \file       mco-core_SlowRandom.hpp
 *  \author     Francois Best
 *  \date       03/11/2013
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

inline SlowRandom::SlowRandom()
{
}

inline SlowRandom::~SlowRandom()
{
}

// -----------------------------------------------------------------------------

inline void SlowRandom::process(Pitch& ioPitch)
{
    const Filter::Sample sample = rand() & 0x07;
    mFilter.samples[mFilter.writeIndex++] = sample;
    mFilter.writeIndex &= (Filter::Size - 1);

    int16 sum = 0;
    for (byte i = 0; i < Filter::Size; ++i)
    {
        sum += mFilter.samples[i];
    }
    sum >>= Filter::Shift;

    ioPitch.cents += sum;
    ioPitch.computeRange();
}

END_MCO_CORE_NAMESPACE
