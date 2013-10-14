/*!
 *  \file       mco-firmware_Settings.h
 *  \author     Francois Best
 *  \date       22/02/2013
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

BEGIN_MCO_FIRMWARE_NAMESPACE

// Deprecated

#define MCO_CLOCK_POLARITY          1   // 0: Start at GND | 1: Start at VCC.
#define MCO_CLOCK_PULSE             0   // 0: Variable PW  | 1: Short pulse.

#define MCO_MODULATION_TUNING       0   // Replace mod with full range control.
#define MCO_MODULATION_FILTER       1   // Activate 16x oversampling.

#define MCO_SPI_ONE_BYTE_PARSING    0   // 0: Parse buffer   | 1: parse 1 byte.
#define MCO_SPI_SLAVE_SELECT        0   // 0: Always listen  | 1: use SS pin.

#define MCO_SYNC_ON_RISING_EDGE     0
#define MCO_SYNC_ON_FALLING_EDGE    0

END_MCO_FIRMWARE_NAMESPACE
