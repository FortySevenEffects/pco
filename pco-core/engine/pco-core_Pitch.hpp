#pragma once

BEGIN_PCO_CORE_NAMESPACE

inline Pitch::Pitch()
    : semitones(0)
    , cents(0)
{
}

inline Pitch::Pitch(Semitones inSemitones, Cents inCents)
    : semitones(inSemitones)
    , cents(inCents)
{
    computeRange();
}

inline Pitch::~Pitch()
{
}

// -----------------------------------------------------------------------------

inline Pitch& Pitch::operator=(const Pitch& inPitch)
{
    semitones = inPitch.semitones;
    cents = inPitch.cents;
    computeRange();
    return *this;
}

inline Pitch& Pitch::operator+=(const Pitch& inPitch)
{
    semitones += inPitch.semitones;
    cents += inPitch.cents;
    computeRange();
    return *this;
}

inline Pitch& Pitch::operator-=(const Pitch& inPitch)
{
    semitones -= inPitch.semitones;
    cents -= inPitch.cents;
    computeRange();
    return *this;
}

// -----------------------------------------------------------------------------

inline Pitch::FlatPitch Pitch::flatten() const
{
    // Here we assume the pitch is positive (not to be used on modulation)
    return semitones * 100 + cents;
}

inline void Pitch::computeRange()
{
    while (cents >= 100)
    {
        semitones++;
        cents -= 100;
    }
    while (cents < 0)
    {
        semitones--;
        cents += 100;
    }
}

inline void Pitch::limit()
{
    if (semitones < 0)
    {
        semitones = 0;
    }
}

// -----------------------------------------------------------------------------

inline Pitch operator+(const Pitch& inA, const Pitch& inB)
{
    Pitch out(inA);
    out += inB;
    out.computeRange();
    return out;
}

inline Pitch operator-(const Pitch& inA, const Pitch& inB)
{
    Pitch out(inA);
    out -= inB;
    out.computeRange();
    return out;
}

END_PCO_CORE_NAMESPACE
