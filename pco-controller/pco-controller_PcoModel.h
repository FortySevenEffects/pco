#pragma once

#include "pco-controller.h"
#include <pco-common_Messages.h>
#include <engine/pco-core_Pitch.h>

BEGIN_PCO_CONTROLLER_NAMESPACE

/*! Expected Traits content:
 *  typedef cake::SpiMaster SpiInterface
 *  typedef cake::Pin       SlaveSelectPin
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

    inline void setPortamentoTime(unsigned inTime);
    inline void setPortamentoBend(byte inBend);

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
