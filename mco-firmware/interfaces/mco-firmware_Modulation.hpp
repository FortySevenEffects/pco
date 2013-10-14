/*!
 *  \file       mco-core_Modulation.hpp
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

BEGIN_MCO_CORE_NAMESPACE

inline void ModulationFilter::init()
{
    // We could do this, but the whole memory is wiped to zero at boot time..
    // mWriteIndex = 0;
    // for (byte i = 0; i < sBufferSize; ++i)
    // {
    //     mBuffer[i] = 0;
    // }
}

inline AdcSample ModulationFilter::process(AdcSample inSample)
{
    mBuffer[mWriteIndex++] = inSample;
    mWriteIndex &= (sBufferSize - 1);
    
    uint16 sum = 0;
    for (byte i = 0; i < sBufferSize; ++i)
    {
        sum += mBuffer[i];
    }
    return sum >> sOversamplingShift;
}

// -----------------------------------------------------------------------------

inline void ModulationInput::init()
{
    mFilter.init();
    mRange = 1800;
    
    // set a2d prescale factor to 128
    // 16 MHz / 128 = 125 KHz, inside the desired 50-200 KHz range.
    ADCSRA |= (1 << ADPS2);
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 << ADPS0);
    
    // enable a2d conversions
    ADCSRA |= (1 << ADEN);
    ADMUX = MCO_MODULATION_PIN;         // Select channel
    DIDR0 |= (1 << MCO_MODULATION_PIN); // Disable digital logic (saves power)
}

inline AdcSample ModulationInput::read() const
{
    ADCSRA |= (1 << ADSC);              // Start conversion
    while (bit_is_set(ADCSRA, ADSC))
    {
        // Wait until it's finished
    }
    
    // Read data, LSB first.
    const byte lsb = ADCL;
    const byte msb = ADCH;
    
    return (msb << 8) | lsb;
}

inline void ModulationInput::process(Pitch& ioPitch)
{
    if (flagbox::isSet<Flags::ModulationEnabled>())
    {
#if MCO_MODULATION_FILTER
        const AdcSample sample = mFilter.process(read());
        static const byte shift = sAdcOvsResolution;
#else
        const AdcSample sample = read();
        static const byte shift = sAdcBitResolution;
#endif
        
#if MCO_MODULATION_TUNING
        ioPitch.semitones = 0;
        ioPitch.cents = (uint32(sample) * 12799) >> shift;
#else
        ioPitch.cents += ((uint32(sample) * mRange * 2) >> shift) - mRange;
#endif
        ioPitch.computeRange();
    }
}

inline void ModulationInput::setRange(Pitch& inRange)
{
    // [0, sAdcMax] -> [-range, +range] cents
    // Example range values:
    // 3000: 1V/Octave, based on a 5V sampling.
    // 1200: +1 octave @ 5V, -1 @ 0V.
    mRange = inRange.semitones * 100 + inRange.cents;
}

END_MCO_CORE_NAMESPACE
