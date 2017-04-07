#pragma once

#include "pco-core.h"
#include "pco-core_Defs.h"

BEGIN_PCO_CORE_NAMESPACE

struct Pitch
{
    typedef int8    Semitones;
    typedef int16   Cents;
    typedef uint16  FlatPitch;

    inline Pitch();
    inline Pitch(Semitones inSemitones, Cents inCents);
    inline ~Pitch();

    inline Pitch& operator=(const Pitch& inPitch);
    inline Pitch& operator+=(const Pitch& inPitch);
    inline Pitch& operator-=(const Pitch& inPitch);

    inline FlatPitch flatten() const;
    inline void computeRange();
    inline void limit();

    Semitones semitones;
    Cents cents;
};

inline Pitch operator+(const Pitch& inA, const Pitch& inB);
inline Pitch operator-(const Pitch& inA, const Pitch& inB);

END_PCO_CORE_NAMESPACE

#include "engine/pco-core_Pitch.hpp"
