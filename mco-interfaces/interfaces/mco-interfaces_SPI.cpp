/*!
 *  \file       mco-core_SPI.cpp
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

#include "interfaces/mco-core_SPI.h"
#include "engine/mco-core_Engine.h"
#include "engine/mco-core_FlagBox.h"

BEGIN_MCO_CORE_NAMESPACE

END_MCO_CORE_NAMESPACE

// -----------------------------------------------------------------------------

/*
#if defined(USI_OVF_vect)
#define SPI_EOT_ISR USI_OVF_vect
#elif defined(SPI_STC_vect)
#define SPI_EOT_ISR SPI_STC_vect
#endif

ISR(SPI_EOT_ISR)
{
#if MCO_SPI_SLAVE_SELECT
    const bool slaveSelected = !(MCO_SPI_READ & (1 << MCO_SPI_SS));
#else
    const bool slaveSelected = true;
#endif
    
#if defined(USISR)
    USISR |= (1 << USIOIF); // Clear "data received" interrupt flag
#endif

    if (slaveSelected)
    {
        mco_core::SPI::sInstance.handleByteReceived();
    }
}

*/
