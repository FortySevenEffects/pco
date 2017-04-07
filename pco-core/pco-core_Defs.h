#pragma once

#include "pco-core.h"
#include <ak47_Types.h>

// 14-bit limited values (still stored on 16 bits).
typedef uint16  uint14;
typedef int16   int14;

// 7-bit limited values (still stored on 8 bits).
typedef uint8   uint7;
typedef int8    int7;

// -----------------------------------------------------------------------------

BEGIN_PCO_CORE_NAMESPACE

typedef uint14 Amount;
static const Amount sAmountMax  = 0x3fff;
static const uint8 sAmountShift = 14;

// -----------------------------------------------------------------------------

typedef Amount  Frequency;          // Amount passed to FrequencyMapper
typedef uint16  Phase;
typedef int16   ModSample;          // Modulation sample
typedef uint32  FixedPointFreq;     // Fixed point frequency, 1 = 0.001 Hz

// -----------------------------------------------------------------------------

typedef int16 PulseWidth;
static const uint8 sPulseWidthShift = 15;

// -----------------------------------------------------------------------------

static const ModSample sModSampleMax = 32767;
static const ModSample sModSampleMin = -1 * sModSampleMax;

// -----------------------------------------------------------------------------

// Match tick timer settings here
static const uint32 sTickPrescale   = 8;
static const uint32 sTickTimerWidth = 256;
static const uint32 sTickFrequency = F_CPU / (sTickPrescale * sTickTimerWidth);

END_PCO_CORE_NAMESPACE
