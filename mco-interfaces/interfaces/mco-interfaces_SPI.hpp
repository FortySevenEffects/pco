/*!
 *  \file       mco-interfaces_SPI.hpp
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

BEGIN_MCO_INTERFACES_NAMESPACE

template<class Traits>
inline SpiInterface<Traits>::SpiInterface(Engine& inEngine)
    : mEngine(inEngine)
{
}

template<class Traits>
inline SpiInterface<Traits>::~SpiInterface()
{
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void SpiInterface<Traits>::init()
{
    Traits::MisoPin::setOutput();
    Traits::MosiPin::setInput();
    Traits::SckPin::setInput();
    Traits::SsPin::setInput(true); // Active low
    Super::open();
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void SpiInterface<Traits>::read()
{
    byte data = 0;
    while (Super::read(data))
    {
        parse(data);
    }
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void SpiInterface<Traits>::parse(byte inData)
{
    if (mIndex == 0)
    {
        // Start a new message
        if (mco_common::MessageStatus::isValidStatus(inData))
        {
            // Status byte
            mMessage[0] = inData;
            mIndex = 1;
            mLength = mco_common::MessageStatus::getLength(inData);
        }
    }
    else
    {
        mMessage[mIndex++] = inData;
    }

    if (mLength != 0 && mIndex == mLength)
    {
        dispatch();
        mIndex = 0;
    }
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void SpiInterface<Traits>::handleByteReceived()
{
    const bool slaveSelected = !Traits::SsPin::read(); // Active low
    Super::handleByteReceived(slaveSelected);
}

// -----------------------------------------------------------------------------

template<class Traits>
void SpiInterface<Traits>::dispatch()
{
    using namespace mco_common;
    switch (mMessage[0])
    {
        case MessageStatus::CoarseNote:
            mEngine.setPitch(mco_core::Pitch(mMessage[1], 0));
            break;
        case MessageStatus::FineNote:
            mEngine.setPitch(mco_core::Pitch(mMessage[1], mMessage[2]));
            break;

        case MessageStatus::GlobalDetune:
        {
            const int14 detune = mco_core::decode_s14(mMessage[1], mMessage[2]);
            mEngine.setDetune(mco_core::Pitch(detune / 100, detune % 100));
        }
            break;

        // ---------------------------------------------------------------------
/*
        case MessageStatus::ModulationRange:
        {
            mco_core::Pitch range(mMessage[1], mMessage[2]);
            mEngine.mModulation.setRange(range);
        }
            break;

        case MessageStatus::EnableModulation:
            flagbox::set<Flags::ModulationEnabled>();
            break;
        case MessageStatus::DisableModulation:
            flagbox::clear<Flags::ModulationEnabled>();
            break;
*/
        // ---------------------------------------------------------------------

        // case MessageStatus::EnableSync:
        //     Sync::setEnabled(true);
        //     break;
        // case MessageStatus::DisableSync:
        //     Sync::setEnabled(false);
        //     break;

        // ---------------------------------------------------------------------

        case MessageStatus::PortamentoTime:
            mEngine.mPortamento.setDuration(mco_core::decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::PortamentoLinearity:
            mEngine.mPortamento.setLinearity(mMessage[1] << 1);
            break;

        // ---------------------------------------------------------------------

        case MessageStatus::VibratoSpeed:
            mEngine.mVibrato.setSpeed(mco_core::decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::VibratoAmount:
            mEngine.mVibrato.setAmount(mco_core::decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::VibratoWaveform:
            mEngine.mVibrato.setWaveform(mMessage[1]);
            break;

        // ---------------------------------------------------------------------

        case MessageStatus::PwmBaseLevel:
            mEngine.mPWM.setBaseLevel(mco_core::decode_s14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::PwmSpeed:
            mEngine.mPWM.setSpeed(mco_core::decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::PwmAmount:
            mEngine.mPWM.setAmount(mco_core::decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::PwmWaveform:
            mEngine.mPWM.setWaveform(mMessage[1]);
            break;

        // ---------------------------------------------------------------------

        case MessageStatus::Mute:
            mEngine.mute();
            break;

        case MessageStatus::Unmute:
            mEngine.unmute();
            break;

        case MessageStatus::ResetPhase:
            mEngine.handleSyncPulse();
            break;

        default:
            break;
    }
}

END_MCO_INTERFACES_NAMESPACE
