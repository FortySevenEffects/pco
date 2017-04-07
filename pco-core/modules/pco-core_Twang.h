#pragma once

#include "pco-core.h"
#include "engine/pco-core_Pitch.h"
#include "modules/pco-core_LFO.h"
#include "modules/pco-core_Envelope.h"

BEGIN_PCO_CORE_NAMESPACE

template<class Traits>
class Twang
{
private:
    typedef typename Traits::EnvelopeMapper     EnvelopeMapper;
    typedef typename Traits::LfoMapper          LfoMapper;

    typedef DecayEnvelope<EnvelopeMapper>       Envelope;
    typedef LFO<LfoMapper>                      Lfo;

public:
    typedef typename Envelope::BendAmount       BendAmount;

public:
    inline  Twang();
    inline ~Twang();

public:
    inline void init();

public:
    inline void process(Pitch& ioPitch);
    inline void process(ModSample& ioSample);
    inline void trigger();
    inline void tick();

public: // Oscillation parameters
    inline void setFrequency(Frequency inFreq);
    inline void setWaveform(byte inWaveform);

public: // Envelope parameters
    inline void setDuration(TimeFactor inDecay);
    inline void setBend(BendAmount inAmount);
    inline void setAmount(Amount inAmount);

private:
    Lfo mLfo;
    Envelope mEnvelope;
    Amount mAmount;
};

END_PCO_CORE_NAMESPACE

#include "modules/pco-core_Twang.hpp"
