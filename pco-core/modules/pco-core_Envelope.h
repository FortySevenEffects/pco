#pragma once

#include "pco-core.h"
#include "pco-core_Defs.h"
#include "engine/pco-core_TickCounter.h"
#include "engine/pco-core_Math.h"
#include "engine/pco-core_Tables.h"

BEGIN_PCO_CORE_NAMESPACE

template<class Mapper> class AdsrEnvelope;

template<class Mapper>
class DecayEnvelope
    : public TickCounter
{
public:
    typedef UModSample  Sample;
    typedef uint7       BendAmount; // 0: linear ; 0x7f: exponential

public:
    inline  DecayEnvelope();
    inline ~DecayEnvelope();

public:
    inline void init();
    inline void process(Sample& outSample);
    inline void trigger();
    inline void setDuration(TimeFactor inDuration);
    inline void setBend(BendAmount inAmount);

public:
    inline bool isActive() const;

private:
    static inline Phase computePhaseIncrement(TimeFactor inTime);
    inline void setPhaseIncrement(Phase inIncrement);

private:
    inline bool updatePhase();
    inline void processLinear(Sample& outSample);
    inline void processExponential(Sample& outSample);

private:
    bool mProcessing;
    Phase mPhase;
    Phase mPhaseIncrement;
    BendAmount mBendAmount;

private:
    friend class AdsrEnvelope<Mapper>;
};

// -----------------------------------------------------------------------------

template<class Mapper>
class AdsrEnvelope
{
public:
    typedef DecayEnvelope<Mapper>               CoreEnvelope;
    typedef typename CoreEnvelope::Sample       Sample;
    typedef typename CoreEnvelope::BendAmount   BendAmount;

    enum State
    {
          idle = 0
        , attack
        , decay
        , sustain
        , release
    };

public:
    inline  AdsrEnvelope();
    inline ~AdsrEnvelope();

public:
    inline void init();
    inline void process(Sample& outSample);
    inline void tick();

public:
    inline void gateOn();
    inline void gateOff();

public:
    inline void setAttack(TimeFactor inAttack);
    inline void setDecay(TimeFactor inDecay);
    inline void setSustain(Sample inLevel);
    inline void setRelease(TimeFactor inRelease);
    inline void setBend(BendAmount inAmount);

private:
    inline void changeState();
    inline void processAttack(Sample& outSample);
    inline void processDecay(Sample& outSample);
    inline void processSustain(Sample& outSample);
    inline void processRelease(Sample& outSample);

private:
    Phase mAttackPhaseIncr;
    Phase mDecayPhaseIncr;
    Sample mSustainLevel;
    Phase mReleasePhaseIncr;

    State mState;
    CoreEnvelope mCore;
    Sample mPreviousSample;
};

END_PCO_CORE_NAMESPACE

#include "modules/pco-core_Envelope.hpp"
