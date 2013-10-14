/*!
 *  \file       mco-firmware_Modulation.h
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

#include "mco-firmware.h"
#include "core/mco-firmware_PinMapping.h"
#include "core/mco-firmware_Settings.h"
#include <engine/mco-core_Pitch.h>
#include <engine/mco-core_FlagBox.h>

BEGIN_MCO_FIRMWARE_NAMESPACE

typedef uint16 AdcSample;

class ModulationFilter
{
public:
     ModulationFilter();
    ~ModulationFilter();
    
public:
    inline void init();
    inline AdcSample process(AdcSample inSample);
    
public:
    // Oversampling is set to 16x, to reach a 12 bit output.
    // We need to sum 16 samples and right-shift by 2.
    static const byte sBufferSize           = 16;
    static const byte sOversamplingShift    = 2;
    
private:
    AdcSample   mBuffer[sBufferSize];
    uint8       mWriteIndex;
};

// -----------------------------------------------------------------------------

class ModulationInput
{
private:
    static const byte   sAdcBitResolution = 10;
    static const byte   sAdcOvsResolution = sAdcBitResolution + ModulationFilter::sOversamplingShift;
    static const uint16 sAdcMax = (1 << sAdcOvsResolution) - 1;
    
public:
     ModulationInput();
    ~ModulationInput();
    
    static ModulationInput sInstance;
    
public:
    inline void init();
    
private:
    inline AdcSample read() const;
    
public:
    inline void process(Pitch& ioPitch);
    inline void setRange(Pitch& inRange);
    
private:
    ModulationFilter    mFilter;
    uint16              mRange;
};

END_MCO_FIRMWARE_NAMESPACE

#include "interfaces/mco-firmware_Modulation.hpp"
