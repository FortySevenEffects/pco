/*!
 *  \file       mco-controller_McoModel.h
 *  \author     Francois Best
 *  \date       15/10/2013
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

#include "mco-controller.h"
#include <mco-common_Messages.h>
#include <engine/mco-core_Pitch.h>

BEGIN_MCO_CONTROLLER_NAMESPACE

/*! Expected Traits content:
 *  typedef ak47::SpiMaster SpiInterface
 *  typedef ak47::Pin       SlaveSelectPin
 */
template<class Traits>
class McoModel
{
public:
    typedef typename Traits::SpiInterface   Spi;

public:
    inline  McoModel(Spi& inInterface);
    inline ~McoModel();

public:
    inline void init();

public:
    inline void setPitch(const mco_core::Pitch& inPitch);
    inline void setDetune(const mco_core::Pitch& inPitch);

    inline void setPortamentoTime(unsigned inTime);
    inline void setPortamentoBend(byte inBend);

    inline void setVibratoSpeed(unsigned inSpeed);
    inline void setVibratoAmount(unsigned inAmount);
    inline void setVibratoWaveform(byte inWaveform);

    inline void setPwmSpeed(unsigned inSpeed);
    inline void setPwmAmount(unsigned inAmount);
    inline void setPwmWaveform(byte inWaveform);

public:
    inline void sendBoolParameter(mco_common::MessageStatus::Status inMessage);

private:
    struct ScopedSlaveSelector
    {
        inline  ScopedSlaveSelector();
        inline ~ScopedSlaveSelector();
    };

private:
    Spi& mInterface;
};

END_MCO_CONTROLLER_NAMESPACE

#include "mco-controller_McoModel.hpp"
