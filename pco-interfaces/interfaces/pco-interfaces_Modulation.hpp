/*!
 *  \file       pco-core_Modulation.hpp
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

BEGIN_PCO_INTERFACES_NAMESPACE

template<class Traits>
inline ModulationInput<Traits>::ModulationInput()
{
}

template<class Traits>
inline ModulationInput<Traits>::~ModulationInput()
{
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void ModulationInput<Traits>::init()
{
    mRange = 1200;

    ak47::Adc::enable();
    ak47::Adc::setPrescaler(ak47::Adc::prescale128);
    Traits::AdcPin::init();
}

template<class Traits>
inline void ModulationInput<Traits>::process(pco_core::Pitch& ioPitch)
{
    const Sample sample = mFilter.process(Traits::AdcPin::read());
    static const byte shift = Traits::sNumBits;
    ioPitch.cents += ((uint32(sample) * mRange * 2) >> shift) - mRange;
    ioPitch.computeRange();
}

template<class Traits>
inline void ModulationInput<Traits>::setRange(pco_core::Pitch& inRange)
{
    // [0, sAdcMax] -> [-range, +range] cents
    // Example range values:
    // 3000: 1V/Octave, based on a 5V sampling.
    // 1200: +1 octave @ 5V, -1 @ 0V.
    mRange = inRange.semitones * 100 + inRange.cents;
}

END_PCO_INTERFACES_NAMESPACE
