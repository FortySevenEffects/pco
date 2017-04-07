#pragma once

#include "pco-common.h"

BEGIN_PCO_COMMON_NAMESPACE

struct MessageStatus
{
    enum
    {                               // Data structure:
        Invalid             = 0x00  // For error detection
        , CoarseNote        = 0x80  // [Semitones]
        , FineNote          = 0x81  // [Semitones]  [Cents]
        , GlobalDetune      = 0x82  // [MSB]        [LSB]   (14 bits signed)
        , ModulationRange   = 0x83  // [MSB]        [LSB]   (14 bits unsigned)
        , PortamentoAmount  = 0x84  // [MSB]        [LSB]   (14 bits unsigned)
        , PortamentoMode    = 0x85  // [Mode]
        , VibratoSpeed      = 0x86  // [MSB]        [LSB]   (14 bits unsigned)
        , VibratoAmount     = 0x87  // [MSB]        [LSB]   (14 bits unsigned)
        , VibratoWaveform   = 0x88  // [Waveform]
        , PwmBaseLevel      = 0x89  // [MSB]        [LSB]   (14 bits signed)
        , PwmSpeed          = 0x8A  // [MSB]        [LSB]   (14 bits unsigned)
        , PwmAmount         = 0x8B  // [MSB]        [LSB]   (14 bits unsigned)
        , PwmWaveform       = 0x8C  // [Waveform]
        , EnableModulation  = 0x8D  // Status only
        , DisableModulation = 0x8E  // Status only
        , EnableSync        = 0x8F  // Status only
        , DisableSync       = 0x90  // Status only
        , EnablePortamento  = 0x91  // Status only
        , DisablePortamento = 0x92  // Status only
        , Mute              = 0x93  // Status only
        , Unmute            = 0x94  // Status only
        , ResetPhase        = 0x95  // Status only

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
        else if (inStatus == CoarseNote         ||
                 inStatus == PortamentoMode     ||
                 inStatus == VibratoWaveform    ||
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

END_PCO_COMMON_NAMESPACE
