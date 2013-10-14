/*!
 *  \file       mco-core_Tables.cpp
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

#include "engine/mco-core_Tables.h"
#include <avr/pgmspace.h>

BEGIN_MCO_CORE_NAMESPACE

// -----------------------------------------------------------------------------
// Timer lookup tables - stored in flash memory to save RAM.

const uint16 gCentInterpolTable[99] PROGMEM = 
{
    65498, 65460, 65423, 65385, 65347, 65309, 65272, 65234, 
    65196, 65159, 65121, 65083, 65046, 65008, 64971, 64933,
    64896, 64858, 64821, 64783, 64746, 64708, 64671, 64634,
    64596, 64559, 64522, 64485, 64447, 64410, 64373, 64336, 
    64299, 64261, 64224, 64187, 64150, 64113, 64076, 64039, 
    64002, 63965, 63928, 63891, 63854, 63818, 63781, 63744, 
    63707, 63670, 63634, 63597, 63560, 63523, 63487, 63450, 
    63413, 63377, 63340, 63304, 63267, 63231, 63194, 63158, 
    63121, 63085, 63048, 63012, 62975, 62939, 62903, 62866, 
    62830, 62794, 62757, 62721, 62685, 62649, 62613, 62576, 
    62540, 62504, 62468, 62432, 62396, 62360, 62324, 62288, 
    62252, 62216, 62180, 62144, 62108, 62073, 62037, 62001, 
    61965, 61929, 61893
};


const uint32 gClockDivision[12] PROGMEM =
{
    // We are using one set of clock divisions for the lowest octave.
    // Other octaves are computed by right-shifting these values.
#if (F_CPU == 16000000)
    1956995, 1847158, 1743485, 1645630, 1553268, 1466090, 
    1383805, 1306138, 1232830, 1163636, 1098326, 1036682
#elif (F_CPU == 20000000)
    2446244, 2308947, 2179356, 2057038, 1941585, 1832612,
    1729756, 1632672, 1541037, 1454545, 1372908, 1295853
#else
#   error Calculate clock division for this frequency.
#endif
};


const byte gPrescaleShift[5] PROGMEM = 
{
    0, 3, 6, 8, 10
};

const int16 gHalfSine[256] PROGMEM = 
{
    0,     402,   804,   1206,  1607,  2009,  2410,  2811,  
    3211,  3611,  4011,  4409,  4807,  5205,  5601,  5997,  
    6392,  6786,  7179,  7571,  7961,  8351,  8739,  9126,  
    9511,  9895,  10278, 10659, 11038, 11416, 11792, 12166, 
    12539, 12909, 13278, 13645, 14009, 14372, 14732, 15090, 
    15446, 15799, 16150, 16499, 16845, 17189, 17530, 17868, 
    18204, 18537, 18867, 19194, 19519, 19840, 20159, 20474, 
    20787, 21096, 21402, 21705, 22004, 22301, 22594, 22883, 
    23169, 23452, 23731, 24006, 24278, 24546, 24811, 25072, 
    25329, 25582, 25831, 26077, 26318, 26556, 26789, 27019, 
    27244, 27466, 27683, 27896, 28105, 28309, 28510, 28706, 
    28897, 29085, 29268, 29446, 29621, 29790, 29955, 30116, 
    30272, 30424, 30571, 30713, 30851, 30984, 31113, 31236, 
    31356, 31470, 31580, 31684, 31785, 31880, 31970, 32056, 
    32137, 32213, 32284, 32350, 32412, 32468, 32520, 32567, 
    32609, 32646, 32678, 32705, 32727, 32744, 32757, 32764, 
    32767, 32764, 32757, 32744, 32727, 32705, 32678, 32646, 
    32609, 32567, 32520, 32468, 32412, 32350, 32284, 32213, 
    32137, 32056, 31970, 31880, 31785, 31684, 31580, 31470, 
    31356, 31236, 31113, 30984, 30851, 30713, 30571, 30424, 
    30272, 30116, 29955, 29790, 29621, 29446, 29268, 29085, 
    28897, 28706, 28510, 28309, 28105, 27896, 27683, 27466, 
    27244, 27019, 26789, 26556, 26318, 26077, 25831, 25582, 
    25329, 25072, 24811, 24546, 24278, 24006, 23731, 23452, 
    23169, 22883, 22594, 22301, 22004, 21705, 21402, 21096, 
    20787, 20474, 20159, 19840, 19519, 19194, 18867, 18537, 
    18204, 17868, 17530, 17189, 16845, 16499, 16150, 15799, 
    15446, 15090, 14732, 14372, 14009, 13645, 13278, 12909, 
    12539, 12166, 11792, 11416, 11038, 10659, 10278, 9895,  
    9511,  9126,  8739,  8351,  7961,  7571,  7179,  6786,  
    6392,  5997,  5601,  5205,  4807,  4409,  4011,  3611,  
    3211,  2811,  2410,  2009,  1607,  1206,  804,   402
};

const uint16 gLogTable[129] PROGMEM = 
{
    40,    43,    45,    48,    51,    54,    57,    60,
    64,    68,    72,    76,    81,    85,    91,    96,
    102,   108,   114,   121,   128,   136,   144,   152,
    161,   171,   181,   192,   203,   215,   228,   242,
    256,   271,   287,   304,   323,   342,   362,   384,
    406,   431,   456,   483,   512,   542,   575,   609,
    645,   683,   724,   767,   813,   861,   912,   967,
    1024,  1085,  1149,  1218,  1290,  1367,  1448,  1534,
    1625,  1722,  1825,  1933,  2048,  2170,  2299,  2435, 
    2580,  2734,  2896,  3069,  3251,  3444,  3649,  3866,
    4096,  4340,  4598,  4871,  5161,  5468,  5793,  6137,
    6502,  6889,  7298,  7732,  8192,  8679,  9195,  9742,
    10321, 10935, 11585, 12274, 13004, 13777, 14596, 15464,
    16384, 17358, 18390, 19484, 20643, 21870, 23170, 24548,
    26008, 27554, 29193, 30929, 32768, 34716, 36781, 38968,
    41285, 43740, 46341, 49097, 52016, 55109, 58386, 61858,
    0xffff
};

const uint16 gSlopeTable[12] PROGMEM = 
{
    0xffff, 61858, 58386, 55109, 52016, 49097, 46341, 43740, 41285, 38968, 36781, 34716
};

// -----------------------------------------------------------------------------

uint16 LookupTables::getCentInterpolation(byte inIndex)
{
    return pgm_read_word(&gCentInterpolTable[inIndex]);
}

uint32 LookupTables::getClockDivision(byte inNote)
{
    return pgm_read_dword(&gClockDivision[inNote]);
}

byte LookupTables::getPrescaleShift(byte inIndex)
{
    return pgm_read_byte(&gPrescaleShift[inIndex]);
}

int16 LookupTables::getHalfSine(byte inIndex)
{
    return pgm_read_word(&gHalfSine[inIndex]);
}

uint16 LookupTables::getLog(byte inIndex)
{
    return pgm_read_word(&gLogTable[inIndex]);
}

uint16 LookupTables::getSlope(byte inIndex)
{
    return pgm_read_word(&gSlopeTable[inIndex]);
}

END_MCO_CORE_NAMESPACE
