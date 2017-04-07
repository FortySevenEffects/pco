/*!
 *  \file       pco-controller_PcoModel.h
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

#include "pco-controller.h"
#include <pco-common_Messages.h>
#include <engine/pco-core_Pitch.h>

BEGIN_PCO_CONTROLLER_NAMESPACE

/*! Expected Traits content:
 *  typedef ak47::SpiMaster SpiInterface
 *  typedef ak47::Pin       SlaveSelectPin
 */
template<class Traits>
class PcoModel
{
public:
    typedef typename Traits::SpiInterface   Spi;

public:
    inline  PcoModel(Spi& inInterface);
    inline ~PcoModel();

public:
    inline void init();

public:
    inline void setPitch(const pco_core::Pitch& inPitch);
    inline void setDetune(const pco_core::Pitch& inPitch);

    inline void setPortamentoAmount(unsigned inAmount);
    inline void setPortamentoMode(byte inMode);

    inline void setVibratoSpeed(unsigned inSpeed);
    inline void setVibratoAmount(unsigned inAmount);
    inline void setVibratoWaveform(byte inWaveform);

    inline void setPwmSpeed(unsigned inSpeed);
    inline void setPwmAmount(unsigned inAmount);
    inline void setPwmWaveform(byte inWaveform);

public:
    inline void sendBoolParameter(pco_common::MessageStatus::Status inMessage);

private:
    struct ScopedSlaveSelector
    {
        inline  ScopedSlaveSelector();
        inline ~ScopedSlaveSelector();
    };

private:
    Spi& mInterface;
};

END_PCO_CONTROLLER_NAMESPACE

#include "pco-controller_PcoModel.hpp"
