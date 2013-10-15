/*!
 *  \file       mco-interfaces_Slope.hpp
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

BEGIN_MCO_INTERFACES_NAMESPACE

Slope::Slope()
{
}

Slope::~Slope()
{
}

inline void Slope::init()
{

    // TCCR0A = (1 << COM0A1) | (0 << COM0A0) | // Non inverting fast PWM
    //          (1 << COM0B1) | (0 << COM0B0) | // Non inverting fast PWM
    //          (1 << WGM01)  | (1 << WGM00);   // Fast PWM
    
    enum
    {
        prescale1       = 0x01,
        prescale8       = 0x02,
        prescale64      = 0x03,
        prescale256     = 0x04,
        prescale1024    = 0x04,
    };

    //MCO_SLOPE_MSB_DDR |= (1 << MCO_SLOPE_MSB_PIN);
    //MCO_SLOPE_LSB_DDR |= (1 << MCO_SLOPE_LSB_PIN);
    
    TCCR0B = prescale1;
}

inline void Slope::setValue(uint64 inClockDivision)
{
    // Slope PWM output is a 16 bit signal shared between two 8 bit channels.
    // The response should match the following constraints:
    // - Low values for low frequencies
    // - High values for high frequencies
    // - Exponential response: freq * 2 -> slope * 2

    // Since ClockDivision is a time measure, we have to invert it.
    const uint64 comp = 0xffffffff;
    const uint64 inverted = comp / inClockDivision;

    const uint16 value = inverted >> 8;
    
    // \todo Find out the meaning of this:
    // Using (clock division - min) * (max PWM - max clock)
    
    internalSetValue(value);
}

inline void Slope::setValue(uint8 inOctave,
                            uint8 inSemiIndex,
                            uint8 inCents)
{
    uint16 semiValue = LookupTables::getSlope(inSemiIndex);

    if (inCents != 0)
    {
        uint32 interpolated = uint32(semiValue);
        interpolated *= LookupTables::getCentInterpolation(inCents - 1);
        semiValue = interpolated >> 16;
    }

    const uint16 value = semiValue >> inOctave;

    internalSetValue(value);
}

// -----------------------------------------------------------------------------

inline void Slope::internalSetValue(uint16 inValue)
{
    OCR0A = inValue >> 8;   // MSB
    OCR0B = inValue & 0xff; // LSB
}

END_MCO_INTERFACES_NAMESPACE
