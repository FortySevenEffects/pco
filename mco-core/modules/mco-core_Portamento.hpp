/*!
 *  \file       mco-core_Portamento.hpp
 *  \author     Francois Best
 *  \date       30/01/2013
 *  \license    GPL v3.0 - Copyright Forty Seven Effects 2013
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

BEGIN_MCO_CORE_NAMESPACE

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

        const int16 originFlat = mOriginPitch.flatten();
        const int16 targetFlat = mTargetPitch.flatten();

        // Diff is negative when target > origin to account for negative progression of decay envelope.
        const int16 diff = originFlat - targetFlat;
        const int16 scaledEnvelope = (int32(sample) * diff) >> 16;
        const int16 pitchOffset = originFlat + scaledEnvelope;
        outPitch.cents += pitchOffset;
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

END_MCO_CORE_NAMESPACE
