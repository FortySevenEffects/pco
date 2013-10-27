/*!
 *  \file       mco-core_LFO.hpp
 *  \author     Francois Best
 *  \date       11/02/2013
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

inline LFO::LFO()
{
}

inline LFO::~LFO()
{
}

// -----------------------------------------------------------------------------

inline void LFO::init()
{
    setFrequency(8000);
}

inline void LFO::process(ModSample& outSample)
{
    mBufferedPhase = mPhase;
    switch (mWaveform)
    {
        case Sine:      generateSine(outSample);        break;
        case Square:    generateSquare(outSample);      break;
        case Saw:       generateSaw(outSample);         break;
        case Ramp:      generateRamp(outSample);        break;
        case Triangle:  generateTriangle(outSample);    break;
        default:
            break;
    }
}

inline void LFO::reset()
{
    mPhase = 0;
}

inline void LFO::tick()
{   
    mPrescaleCounter++;
    if (mPrescaleCounter >= mPrescaleThreshold)
    {
        mPhase += mPhaseIncrement;
        mPrescaleCounter = 0;
    }
}

// -----------------------------------------------------------------------------

inline void LFO::setWaveform(byte inWaveform)
{
    mWaveform = inWaveform % numWaveforms;
}

inline void LFO::setFrequency(Frequency inFrequency)
{
    const uint8 index   = inFrequency >> 7;
    const uint8 amount  = inFrequency & 0x7f;
    const uint16 logA   = LookupTables::getLog(index);
    const uint16 logB   = LookupTables::getLog(index + 1);
    
    const uint16 value  = interpol(logA, logB, amount);
    mPrescaleThreshold  = 256;
    mPhaseIncrement     = value;
}

// -----------------------------------------------------------------------------

inline void LFO::generateSine(ModSample& outSample)
{
    // 256 points for half wave -> 512 points for full wave
    // use overflow for index
    // Phase    0                     7fff 8000                  ffff
    // Sign     [ ++++++++++++++++++++++ ] [ ---------------------- ]
    // Index    0                      255 0                      255
    // Factor   1                        1 -1                      -1
    
    const uint8 index = mBufferedPhase >> 7;
    const uint7 alpha = mBufferedPhase & 0x7f;
    const int16 sampleA = LookupTables::getHalfSine(index);
    const int16 sampleB = LookupTables::getHalfSine(index + 1);
    const int16 sign = (mBufferedPhase & 0x8000) ? -1 : 1;
    outSample = sign * interpol(sampleA, sampleB, alpha);
}

inline void LFO::generateSquare(ModSample& outSample)
{
    outSample = (mBufferedPhase & 0x8000) ? sModSampleMax : sModSampleMin;
}

inline void LFO::generateSaw(ModSample& outSample)
{
    outSample = sModSampleMax - mBufferedPhase;
}

inline void LFO::generateRamp(ModSample& outSample)
{
    outSample = sModSampleMin + mBufferedPhase;
}

inline void LFO::generateTriangle(ModSample& outSample)
{
    outSample = (mBufferedPhase & 0x8000) ? sModSampleMax - (2 * (mBufferedPhase & 0x7fff))
                                          : sModSampleMin + 2 * mBufferedPhase;
}

END_MCO_CORE_NAMESPACE
