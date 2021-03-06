#pragma once

#include "pco-interfaces.h"
#include <engine/pco-core_Pitch.h>
#include <io/cake_Analog.h>

BEGIN_PCO_INTERFACES_NAMESPACE

// Expected Traits content:
// static const byte sNumBits        Used for oversampling filter (must be > 10)
// typedef [cake::AnalogPin] AdcPin  Pin to be used for ADC readings

template<class Traits>
class ModulationInput
{
public:
    inline  ModulationInput();
    inline ~ModulationInput();

public:
    inline void init();

public:
    inline void process(pco_core::Pitch& ioPitch);
    inline void setRange(pco_core::Pitch& inRange);

private:
    typedef cake::Adc::Sample Sample;
    cake::AdcOversamplingFilter<Traits::sNumBits> mFilter;
    uint16 mRange;
};

END_PCO_INTERFACES_NAMESPACE

#include "interfaces/pco-interfaces_Modulation.hpp"
