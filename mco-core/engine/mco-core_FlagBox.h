/*!
 *  \file       mco-core_FlagBox.h
 *  \author     Francois Best
 *  \date       15/02/2013
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

#include "mco-core.h"
#include "mco-core_Defs.h"
#include <avr/io.h>

BEGIN_MCO_CORE_NAMESPACE

struct Flags
{
    enum 
    {
        // Flags for General Purpose Register 0

          ClockRefresh          = 0
        , PwmEnabled            = 1
        , VibratoEnabled        = 2
        , PortamentoEnabled     = 3
        , PortamentoActive      = 4

        , numFlags
    };
};

namespace flagbox
{
    typedef uint8 Flag;
    
    // -------------------------------------------------------------------------

    template<Flag inFlag>
    inline bool isSet();

    template<Flag inFlag>
    inline void set();

    template<Flag inFlag>
    inline void clear();
};

END_MCO_CORE_NAMESPACE

#include "engine/mco-core_FlagBox.hpp"
