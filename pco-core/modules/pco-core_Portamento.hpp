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
    // mMode = Linear
}

inline void Portamento::trigger(const Pitch& inTarget)
{
    // Note: this will not handle retriggering correctly.
    mOriginPitch = mTargetPitch;
    mTargetPitch = inTarget;

    if (flagbox::isSet<Flags::PortamentoEnabled>())
    {
        mPhaseCounter = 0;
        mPhase        = 0;
        flagbox::set<Flags::PortamentoActive>();
    }
}

inline void Portamento::process(Pitch& outPitch)
{
    if (flagbox::isSet<Flags::PortamentoActive>())
    {
        mPhase = mPhaseCounter; // \todo Lock this operation
        outPitch = mOriginPitch;
        switch (mMode)
        {
            case Linear:        processLinear(outPitch);        break;
            case Exponential:   processExponential(outPitch);   break;
            default:
                break;
        }
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
    if (flagbox::isSet<Flags::PortamentoActive>())
    {
        // \todo Implement prescale here
        Phase pre = mPhaseCounter;
        mPhaseCounter += 4;
        if (pre > mPhaseCounter)
        {
            // Overflow -> disable portamento and lock on target pitch.
            flagbox::clear<Flags::PortamentoActive>();
        }
    }
}

// -----------------------------------------------------------------------------

inline void Portamento::setAmount(Amount inAmount)
{
    // \todo Check what needs to be done when already running,
    // like recomputing the slope or anything..
}

inline void Portamento::setMode(byte inMode)
{
    mMode = inMode;
}

inline void Portamento::setEnabled(bool inEnabled)
{
    if (inEnabled)
    {
        flagbox::set<Flags::PortamentoEnabled>();
    }
    else
    {
        flagbox::clear<Flags::PortamentoActive>();
        flagbox::clear<Flags::PortamentoEnabled>();
    }
}

// -----------------------------------------------------------------------------

inline void Portamento::processLinear(Pitch& outPitch)
{
    const int32 diff = mTargetPitch.flatten() - int32(mOriginPitch.flatten());
    const int32 offset = (diff * int32(mPhase)) >> 16;
    outPitch.cents += offset;
}

inline void Portamento::processExponential(Pitch& outPitch)
{
    const uint7 index = 127 - (mPhase >> 9);    // Index range: [127-0]
    const uint7 alpha = (mPhase >> 2) & 0x7f;   // \todo this should be reversed.
    const int32 diff = mTargetPitch.flatten() - int32(mOriginPitch.flatten());
    const int32 logA = LookupTables::getLog(index + 1);
    const int32 logB = LookupTables::getLog(index);
    const int32 logI = interpol(logA, logB, alpha);
    const int32 offset = (diff * (0xffff - logI)) >> 16;
    outPitch.cents += offset;
}

END_PCO_CORE_NAMESPACE