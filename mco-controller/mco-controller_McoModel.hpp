/*!
 *  \file       mco-controller_McoModel.hpp
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

BEGIN_MCO_CONTROLLER_NAMESPACE

template<class Traits>
inline McoModel<Traits>::ScopedSlaveSelector::ScopedSlaveSelector()
{
    Traits::SlaveSelectPin::clear();
}

template<class Traits>
inline McoModel<Traits>::ScopedSlaveSelector::~ScopedSlaveSelector()
{
    Traits::SlaveSelectPin::set();
}

// ########################################################################## //

template<class Traits>
inline McoModel<Traits>::McoModel(Spi& inInterface)
    : mInterface(inInterface)
{
}

template<class Traits>
inline McoModel<Traits>::~McoModel()
{
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void McoModel<Traits>::init()
{
    Traits::SlaveSelectPin::setOutput();
    Traits::SlaveSelectPin::set(); // Active low
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void McoModel<Traits>::setPitch(mco_core::Pitch& inPitch)
{
    ScopedSlaveSelector selector;
    mInterface.send(mco_common::MessageStatus::FineNote);
    mInterface.send(inPitch.semitones);
    mInterface.send(inPitch.cents);
}

template<class Traits>
inline void McoModel<Traits>::setDetune(mco_core::Pitch& inPitch)
{
    ScopedSlaveSelector selector;
    mInterface.send(mco_common::MessageStatus::GlobalDetune);
    mInterface.send(inPitch.semitones);
    mInterface.send(inPitch.cents);
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void McoModel<Traits>::sendBoolParameter(mco_common::MessageStatus::Status inMessage)
{
    ScopedSlaveSelector selector;
    mInterface.send(inMessage);
}

END_MCO_CONTROLLER_NAMESPACE
