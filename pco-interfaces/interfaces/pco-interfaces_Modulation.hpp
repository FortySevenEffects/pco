#pragma once

BEGIN_PCO_INTERFACES_NAMESPACE

template<class Traits>
inline ModulationInput<Traits>::ModulationInput()
{
}

template<class Traits>
inline ModulationInput<Traits>::~ModulationInput()
{
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void ModulationInput<Traits>::init()
{
    mRange = 1200;

    ak47::Adc::enable();
    ak47::Adc::setPrescaler(ak47::Adc::prescale128);
    Traits::AdcPin::init();
}

template<class Traits>
inline void ModulationInput<Traits>::process(pco_core::Pitch& ioPitch)
{
    const Sample sample = mFilter.process(Traits::AdcPin::read());
    static const byte shift = Traits::sNumBits;
    ioPitch.cents += ((uint32(sample) * mRange * 2) >> shift) - mRange;
    ioPitch.computeRange();
}

template<class Traits>
inline void ModulationInput<Traits>::setRange(pco_core::Pitch& inRange)
{
    // [0, sAdcMax] -> [-range, +range] cents
    // Example range values:
    // 3000: 1V/Octave, based on a 5V sampling.
    // 1200: +1 octave @ 5V, -1 @ 0V.
    mRange = inRange.semitones * 100 + inRange.cents;
}

END_PCO_INTERFACES_NAMESPACE
