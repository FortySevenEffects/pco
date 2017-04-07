#pragma once

BEGIN_PCO_INTERFACES_NAMESPACE

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
        if (pco_common::MessageStatus::isValidStatus(inData))
        {
            // Status byte
            mMessage[0] = inData;
            mIndex = 1;
            mLength = pco_common::MessageStatus::getLength(inData);
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
    using namespace pco_common;
    switch (mMessage[0])
    {
        case MessageStatus::CoarseNote:
            mEngine.setPitch(pco_core::Pitch(mMessage[1], 0));
            break;
        case MessageStatus::FineNote:
            mEngine.setPitch(pco_core::Pitch(mMessage[1], mMessage[2]));
            break;

        case MessageStatus::GlobalDetune:
        {
            const int14 detune = pco_core::decode_s14(mMessage[1], mMessage[2]);
            mEngine.setDetune(pco_core::Pitch(detune / 100, detune % 100));
        }
            break;

        // ---------------------------------------------------------------------
/*
        case MessageStatus::ModulationRange:
        {
            pco_core::Pitch range(mMessage[1], mMessage[2]);
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
            mEngine.mPortamento.setDuration(pco_core::decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::PortamentoBend:
            mEngine.mPortamento.setBend(mMessage[1]);
            break;

        // ---------------------------------------------------------------------

        case MessageStatus::VibratoSpeed:
            mEngine.mVibrato.setSpeed(pco_core::decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::VibratoAmount:
            mEngine.mVibrato.setAmount(pco_core::decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::VibratoWaveform:
            mEngine.mVibrato.setWaveform(mMessage[1]);
            break;

        // ---------------------------------------------------------------------

        case MessageStatus::PwmBaseLevel:
            mEngine.mPWM.setBaseLevel(pco_core::decode_s14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::PwmSpeed:
            mEngine.mPWM.setSpeed(pco_core::decode_u14(mMessage[1], mMessage[2]));
            break;
        case MessageStatus::PwmAmount:
            mEngine.mPWM.setAmount(pco_core::decode_u14(mMessage[1], mMessage[2]));
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

        // ---------------------------------------------------------------------

        case MessageStatus::EnterTuning:
            mEngine.unmute();
            mEngine.setTuning(true);
            break;

        case MessageStatus::CycleTuningModes:
            mEngine.mTuningModule.cycleMode();
            break;

        case MessageStatus::ExitTuning:
            mEngine.setTuning(false);
            break;

        default:
            break;
    }
}

END_PCO_INTERFACES_NAMESPACE
