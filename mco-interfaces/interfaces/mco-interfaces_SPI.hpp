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
    // Enable pull-ups on input to avoid listening to air wires.
    Traits::MisoPin::setOutput();
    Traits::MosiPin::setInput(true);
    Traits::ClkPin::setInput(true);
    Traits::SsPin::setInput(true);
    Super::open();

/*
#if MCO_SPI_SLAVE_SELECT
    // Setup SS as a pin change interrupt
    GIMSK  |= (1 << PCIE0);             // Enable PCINT on port A
    PCMSK0 |= (1 << MCO_SPI_SS_PCINT);  // Enable interrupt for pin SS
    MCO_SPI_PORT |= (1 << MCO_SPI_SS);  // Enable pull-up for SS

    // Init with current SS pin state.
    handleSS(Traits::SsPin::read());
#endif
*/
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
        if (inData & 0x80)
        {
            // Status byte
            mMessage[0] = inData;
            mIndex = 1;
            mLength = mco_common::MessageStatus::getLength(inData);
        }
        else
        {
            // Data byte, implement running status if needed.
        }
    }
    else
    {
        mMessage[mIndex++] = inData;
    }

    if (mIndex == mLength)
    {
        dispatch();
        mIndex = 0;
    }
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void SpiInterface<Traits>::handleSS(bool inPinState)
{
    /*
    if (inPinState != flagbox::isSet<Flags::SpiSSPinState>())
    {
#if MCO_SPI_SLAVE_SELECT
        const bool slaveSelected = !inPinState; // Selected when SS is low.
#else
        const bool slaveSelected = true;
#endif
        if (slaveSelected)
        {
            MCO_SPI_DDR |= (1 << MCO_SPI_MISO); // MISO = Output
        }
        else
        {
            MCO_SPI_DDR &= ~(1 << MCO_SPI_MISO); // MISO = HiZ
        }

        if (inPinState)     flagbox::set<Flags::SpiSSPinState>();
        else                flagbox::clear<Flags::SpiSSPinState>();
    }
    */
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
/*
        case MessageStatus::GlobalDetune:
        {
            const int14 detune = decode_s14(mMessage[1], mMessage[2]);
            mEngine.setDetune(mco_core::Pitch(detune / 100, detune % 100));
        }
            break;

        // ---------------------------------------------------------------------

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

        // ---------------------------------------------------------------------

        case MessageStatus::EnableSync:
            Sync::sInstance.setEnabled(true);
            break;
        case MessageStatus::DisableSync:
            Sync::sInstance.setEnabled(false);
            break;

        // ---------------------------------------------------------------------

        case MessageStatus::PortamentoAmount:
            mEngine.mPortamento.setAmount(decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::PortamentoMode:
            mEngine.mPortamento.setMode(mMessage[1]);
            break;
        case MessageStatus::EnablePortamento:
            mEngine.mPortamento.setEnabled(true);
            break;
        case MessageStatus::DisablePortamento:
            mEngine.mPortamento.setEnabled(false);
            break;

        // ---------------------------------------------------------------------

        case MessageStatus::VibratoSpeed:
            mEngine.mVibrato.setSpeed(decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::VibratoAmount:
            mEngine.mVibrato.setAmount(decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::VibratoWaveform:
            mEngine.mVibrato.setWaveform(mMessage[1]);
            break;
        case MessageStatus::EnableVibrato:
            flagbox::set<Flags::VibratoEnabled>();
            break;
        case MessageStatus::DisableVibrato:
            flagbox::clear<Flags::VibratoEnabled>();
            break;

        // ---------------------------------------------------------------------

        case MessageStatus::PwmBaseLevel:
            mEngine.mPWM.setBaseLevel(decode_s14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::PwmSpeed:
            mEngine.mPWM.setSpeed(decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::PwmAmount:
            mEngine.mPWM.setAmount(decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::PwmWaveform:
            mEngine.mPWM.setWaveform(mMessage[1]);
            break;
        case MessageStatus::EnablePwm:
            flagbox::set<Flags::PwmEnabled>();
            break;
        case MessageStatus::DisablePwm:
            flagbox::clear<Flags::PwmEnabled>();
            break;

        // ---------------------------------------------------------------------
*/
        default:
            break;
    }
}

END_MCO_INTERFACES_NAMESPACE
