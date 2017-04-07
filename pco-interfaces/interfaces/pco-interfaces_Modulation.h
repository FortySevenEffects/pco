/*!
 *  \file       pco-interfaces_Modulation.h
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
#include <io/ak47_Analog.h>

BEGIN_PCO_INTERFACES_NAMESPACE

// Expected Traits content:
// static const byte sNumBits        Used for oversampling filter (must be > 10)
// typedef [ak47::AnalogPin] AdcPin  Pin to be used for ADC readings

template<class Traits>
class ModulationInput
{
public:
    inline  ModulationInput();
    inline ~ModulationInput();

public:
    inline void init();

public:
    inline void process(pco_core::Pitch& ioPitch);
    inline void setRange(pco_core::Pitch& inRange);

private:
    typedef ak47::Adc::Sample Sample;
    ak47::AdcOversamplingFilter<Traits::sNumBits> mFilter;
    uint16 mRange;
};

END_PCO_INTERFACES_NAMESPACE

#include "interfaces/pco-interfaces_Modulation.hpp"
