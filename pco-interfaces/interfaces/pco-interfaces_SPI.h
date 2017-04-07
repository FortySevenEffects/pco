/*!
 *  \file       pco-interfaces_SPI.h
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
#include <engine/pco-core_Math.h>
#include <pco-common_Messages.h>
#include <io/ak47_Spi.h>

BEGIN_PCO_INTERFACES_NAMESPACE

/*! Expected Traits content:
 * typedef Engine                               PCO Engine
 * typedef ak47::Pin MosiPin                    SPI Pin
 * typedef ak47::Pin MisoPin                    SPI Pin
 * typedef ak47::Pin SckPin                     SPI Pin
 * typedef ak47::Pin SsPin                      SPI Pin
 */
template<class Traits>
class SpiInterface
    : public ak47::SpiSlave<8>
{
private:
    typedef ak47::SpiSlave<8>           Super;
    typedef typename Traits::Engine     Engine;

public:
    inline  SpiInterface(Engine& inEngine);
    inline ~SpiInterface();

public:
    inline void init();
    inline void read();

private:
    inline void parse(byte inData);
    inline void dispatch();

public:
    inline void handleByteReceived();

private:
    Engine& mEngine;
    byte mMessage[pco_common::MessageStatus::sMaxMessageSize];
    byte mIndex;
    byte mLength;
};

END_PCO_INTERFACES_NAMESPACE

#include "interfaces/pco-interfaces_SPI.hpp"
