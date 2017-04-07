#pragma once

#include "pco-core.h"
#include "engine/pco-core_Pitch.h"
#include "engine/pco-core_Mappers.h"
#include "modules/pco-core_Envelope.h"

BEGIN_PCO_CORE_NAMESPACE

class Portamento
{
public:
    static const FixedPointTime sMinTime = 1000;    // 1 ms
    static const FixedPointTime sMaxTime = 4000000; // 4 s

    typedef ExpMapper<FixedPointTime, sMinTime, sMaxTime, 0x7f> EnvelopeMapper;
    typedef DecayEnvelope<EnvelopeMapper>                       Envelope;
    typedef typename Envelope::BendAmount                       BendAmount;

public:
    inline Portamento();
    inline ~Portamento();

public:
    inline void init();
    inline void trigger(const Pitch& inTarget);
    inline void process(Pitch& outPitch);

public:
    inline void tick();

public:
    inline void setDuration(TimeFactor inDuration);
    inline void setBend(BendAmount inAmount);

private:
    Envelope mEnvelope;
    Pitch mTargetPitch;
    Pitch mOriginPitch;
};

END_PCO_CORE_NAMESPACE

#include "modules/pco-core_Portamento.hpp"
