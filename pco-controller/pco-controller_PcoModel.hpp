#pragma once

BEGIN_PCO_CONTROLLER_NAMESPACE

template<class Traits>
inline PcoModel<Traits>::ScopedSlaveSelector::ScopedSlaveSelector()
{
    Traits::SlaveSelectPin::clear();
}

template<class Traits>
inline PcoModel<Traits>::ScopedSlaveSelector::~ScopedSlaveSelector()
{
    Traits::SpiInterface::waitForEndOfTransmission();
    Traits::SlaveSelectPin::set();
}

// ########################################################################## //

template<class Traits>
inline PcoModel<Traits>::PcoModel(Spi& inInterface)
    : mInterface(inInterface)
{
}

template<class Traits>
inline PcoModel<Traits>::~PcoModel()
{
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void PcoModel<Traits>::init()
{
    Traits::SlaveSelectPin::setOutput();
    Traits::SlaveSelectPin::set(); // Active low
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void PcoModel<Traits>::setPitch(const pco_core::Pitch& inPitch)
{
    ScopedSlaveSelector selector;
    mInterface.send(pco_common::MessageStatus::FineNote);
    mInterface.send(inPitch.semitones);
    mInterface.send(inPitch.cents);
}

template<class Traits>
inline void PcoModel<Traits>::setDetune(const pco_core::Pitch& inPitch)
{
    const int16 data = inPitch.semitones * 100 + inPitch.cents;
    ScopedSlaveSelector selector;
    mInterface.send(pco_common::MessageStatus::GlobalDetune);
    mInterface.send((data >> 7) & 0x7f);
    mInterface.send(data & 0x7f);
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void PcoModel<Traits>::setPortamentoAmount(unsigned inAmount)
{
    ScopedSlaveSelector selector;
    mInterface.send(pco_common::MessageStatus::PortamentoAmount);
    mInterface.send(inAmount >> 7);
    mInterface.send(inAmount & 0x7f);
}

template<class Traits>
inline void PcoModel<Traits>::setPortamentoMode(byte inMode)
{
    ScopedSlaveSelector selector;
    mInterface.send(pco_common::MessageStatus::PortamentoMode);
    mInterface.send(inMode);
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void PcoModel<Traits>::setVibratoSpeed(unsigned inSpeed)
{
    ScopedSlaveSelector selector;
    mInterface.send(pco_common::MessageStatus::VibratoSpeed);
    mInterface.send(inSpeed >> 7);
    mInterface.send(inSpeed & 0x7f);
}

template<class Traits>
inline void PcoModel<Traits>::setVibratoAmount(unsigned inAmount)
{
    ScopedSlaveSelector selector;
    mInterface.send(pco_common::MessageStatus::VibratoAmount);
    mInterface.send(inAmount >> 7);
    mInterface.send(inAmount & 0x7f);
}

template<class Traits>
inline void PcoModel<Traits>::setVibratoWaveform(byte inWaveform)
{
    ScopedSlaveSelector selector;
    mInterface.send(pco_common::MessageStatus::VibratoWaveform);
    mInterface.send(inWaveform);
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void PcoModel<Traits>::setPwmSpeed(unsigned inSpeed)
{
    ScopedSlaveSelector selector;
    mInterface.send(pco_common::MessageStatus::PwmSpeed);
    mInterface.send(inSpeed >> 7);
    mInterface.send(inSpeed & 0x7f);
}

template<class Traits>
inline void PcoModel<Traits>::setPwmAmount(unsigned inAmount)
{
    ScopedSlaveSelector selector;
    mInterface.send(pco_common::MessageStatus::PwmAmount);
    mInterface.send(inAmount >> 7);
    mInterface.send(inAmount & 0x7f);
}

template<class Traits>
inline void PcoModel<Traits>::setPwmWaveform(byte inWaveform)
{
    ScopedSlaveSelector selector;
    mInterface.send(pco_common::MessageStatus::PwmWaveform);
    mInterface.send(inWaveform);
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void PcoModel<Traits>::sendBoolParameter(pco_common::MessageStatus::Status inMessage)
{
    ScopedSlaveSelector selector;
    mInterface.send(inMessage);
}

END_PCO_CONTROLLER_NAMESPACE
