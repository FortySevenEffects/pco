#pragma once

BEGIN_PCO_CORE_NAMESPACE

inline Portamento::Portamento()
{
}

inline Portamento::~Portamento()
{
}

// -----------------------------------------------------------------------------

inline void Portamento::init()
{
    mTargetPitch = Pitch(64, 0);
    mEnvelope.init();
}

inline void Portamento::trigger(const Pitch& inTarget)
{
    // Note: this will not handle retriggering correctly.
    mOriginPitch = mTargetPitch;
    mTargetPitch = inTarget;
    mEnvelope.trigger();
}

inline void Portamento::process(Pitch& outPitch)
{
    if (mEnvelope.isActive())
    {
        Envelope::Sample sample = 0;
        mEnvelope.process(sample);
        sample = sUModSampleMax - sample;

        const int16 diff = mTargetPitch.flatten() - mOriginPitch.flatten();
        const int16 scaledEnvelope = (int32(sample) * diff) >> 16;
        outPitch = mOriginPitch;
        outPitch.cents += scaledEnvelope;
        outPitch.computeRange();
    }
    else
    {
        outPitch = mTargetPitch;
    }
}

// -----------------------------------------------------------------------------

inline void Portamento::tick()
{
    mEnvelope.tick();
}

// -----------------------------------------------------------------------------

inline void Portamento::setDuration(TimeFactor inDuration)
{
    mEnvelope.setDuration(inDuration);
}

inline void Portamento::setBend(BendAmount inAmount)
{
    mEnvelope.setBend(inAmount);
}

END_PCO_CORE_NAMESPACE
