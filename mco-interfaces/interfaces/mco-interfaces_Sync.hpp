/*!
 *  \file       mco-interfaces_Sync.hpp
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

BEGIN_MCO_INTERFACES_NAMESPACE

template<class Traits>
inline Sync<Traits>::Sync(Engine& inEngine)
    : mEngine(inEngine)
{
}

template<class Traits>
inline Sync<Traits>::~Sync()
{
}

template<class Traits>
inline void Sync<Traits>::init()
{
    Traits::SyncPin::setInput(true);
    // \todo Activate interrupt
}

template<class Traits>
inline void Sync<Traits>::setEnabled(bool inEnabled)
{
    // \todo Implement me.
}

// -----------------------------------------------------------------------------

template<class Traits>
inline void Sync<Traits>::handleSync(bool inPinState)
{
    // Trigger on falling edge
    if (inPinState == false)
        mEngine.handleSyncPulse();
}

END_MCO_INTERFACES_NAMESPACE
