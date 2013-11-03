/*!
 *  \file       mco-common_Messages.cpp
 *  \author     Francois Best
 *  \date       11/12/2012
 *  \license    GPL v3.0 - Copyright Forty Seven Effects 2012
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

#include "mco-common.h"

BEGIN_MCO_COMMON_NAMESPACE

struct MessageStatus
{
    enum
    {                               // Data structure:
        Invalid                 = 0x00  // For error detection
        , CoarseNote            = 0x80  // [Semitones]
        , FineNote              = 0x81  // [Semitones]  [Cents]
        , GlobalDetune          = 0x82  // [MSB]        [LSB]   (14 bits signed)
        , ModulationRange       = 0x83  // [MSB]        [LSB]   (14 bits unsigned)
        , PortamentoTime        = 0x84  // [MSB]        [LSB]   (14 bits unsigned)
        , PortamentoLinearity   = 0x85  // [Linearity]
        , VibratoSpeed          = 0x86  // [MSB]        [LSB]   (14 bits unsigned)
        , VibratoAmount         = 0x87  // [MSB]        [LSB]   (14 bits unsigned)
        , VibratoWaveform       = 0x88  // [Waveform]
        , PwmBaseLevel          = 0x89  // [MSB]        [LSB]   (14 bits signed)
        , PwmSpeed              = 0x8A  // [MSB]        [LSB]   (14 bits unsigned)
        , PwmAmount             = 0x8B  // [MSB]        [LSB]   (14 bits unsigned)
        , PwmWaveform           = 0x8C  // [Waveform]
        , EnableModulation      = 0x8D  // Status only
        , DisableModulation     = 0x8E  // Status only
        , EnableSync            = 0x8F  // Status only
        , DisableSync           = 0x90  // Status only
        , Mute                  = 0x93  // Status only
        , Unmute                = 0x94  // Status only
        , ResetPhase            = 0x95  // Status only

        , lastAddressedStatus
        , MaximumStatus     = 0xFF
    };
    
    typedef unsigned char Status;
    
    static inline bool isValidStatus(Status inStatus)
    {
        return inStatus >= 0x80 && inStatus < lastAddressedStatus;
    }

    static const unsigned char sMaxMessageSize = 3;
    static inline unsigned char getLength(Status inStatus)
    {
        if (inStatus >= EnableModulation)
        {
            return 1;
        }
        else if (inStatus == CoarseNote          ||
                 inStatus == PortamentoLinearity ||
                 inStatus == VibratoWaveform     ||
                 inStatus == PwmWaveform)
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }
};

END_MCO_COMMON_NAMESPACE
