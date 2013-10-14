/*!
 *  \file       mco-core_SPI.h
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

#include "mco-core.h"
#include "core/mco-core_PinMapping.h"
#include "core/mco-core_Settings.h"
#include "engine/mco-core_Math.h"
#include "engine/mco-core_Pitch.h"
#include "engine/mco-core_Flagbox.h"
#include "interfaces/mco-core_Sync.h"
#include <mco-common_Messages.h>
#include <io/ak47_Spi.h>

BEGIN_MCO_CORE_NAMESPACE

template<class Engine>
class SpiInterface
    : public ak47::SpiSlave<8>
{
public:
    typedef ak47::SpiSlave<8> Super;

public:
    inline  SpiInterface(Engine& inEngine);
    inline ~SpiInterface();

public:
    inline void init();
    inline void read();
    inline const Pitch& getGlobalDetune() const;
    
private:
    inline void parse(byte inData);
    inline void dispatch();
    
public:
    inline void handleSS(bool inPinState);
    
private:
    Engine& mEngine;
    byte mMessage[mco_common::MessageStatus::sMaxMessageSize];
    byte mIndex;
    byte mLength;
};

END_MCO_CORE_NAMESPACE

#include "interfaces/mco-core_SPI.hpp"
