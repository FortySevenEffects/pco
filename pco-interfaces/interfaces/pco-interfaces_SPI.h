#pragma once

#include "pco-interfaces.h"
#include <engine/pco-core_Pitch.h>
#include <engine/pco-core_Math.h>
#include <pco-common_Messages.h>
#include <io/cake_Spi.h>

BEGIN_PCO_INTERFACES_NAMESPACE

/*! Expected Traits content:
 * typedef Engine                               PCO Engine
 * typedef cake::Pin MosiPin                    SPI Pin
 * typedef cake::Pin MisoPin                    SPI Pin
 * typedef cake::Pin SckPin                     SPI Pin
 * typedef cake::Pin SsPin                      SPI Pin
 */
template<class Traits>
class SpiInterface
    : public cake::SpiSlave<8>
{
private:
    typedef cake::SpiSlave<8>           Super;
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
