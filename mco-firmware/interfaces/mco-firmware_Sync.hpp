/*!
 *  \file       mco-firmware_Sync.hpp
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

BEGIN_MCO_FIRMWARE_NAMESPACE

inline void Sync::init()
{
    // We use the PCINT flag as enabled/disabled detection, plus it also
    // enables/disables the actual interrupt, so we don't need to check
    // in the ISR
    
    MCO_SYNC_DDR &= ~(1 << MCO_SYNC_PIN);   // Configure as input
    MCO_SYNC_PCINT_ENABLE_BANK;
    
    setEnabled(false);
}

inline void Sync::setEnabled(bool inEnabled)
{
    if (inEnabled)
    {
        MCO_SYNC_PCINT_ENABLE;
    }
    else
    {
        MCO_SYNC_PCINT_DISABLE;
    }
}

// -----------------------------------------------------------------------------

inline void Sync::handleSync(bool inPinState)
{
    if (inPinState != flagbox::isSet<Flags::SyncPinState>())
    {
#if MCO_SYNC_ON_RISING_EDGE
        if (inPinState == true)
        {
            Timer::sInstance.reset();
        }
#endif
        
#if MCO_SYNC_ON_FALLING_EDGE
        if (inPinState == false)
        {
            Timer::sInstance.reset();
        }
#endif

        if (inPinState) flagbox::set<Flags::SyncPinState>();
        else            flagbox::clear<Flags::SyncPinState>();
    }
}

END_MCO_FIRMWARE_NAMESPACE
