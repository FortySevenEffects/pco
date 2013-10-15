/*!
 *  \file       mco-core_Sync.h
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

#include "mco-interfaces.h"

BEGIN_MCO_INTERFACES_NAMESPACE

/*! Expected Traits contents:
 *  typedef ak47::Pin SyncPin       GPIO pin to use for Sync input
 *  
 */
template<class Traits>
class Sync
{
public:
    typedef typename Traits::Engine Engine;

public:
    inline  Sync(Engine& inEngine);
    inline ~Sync();

public:
    inline void init();
    inline void setEnabled(bool inState);

public:
    inline void handleSync(bool inPinState);

private:
    Engine& mEngine;
};

END_MCO_INTERFACES_NAMESPACE

#include "interfaces/mco-interfaces_Sync.hpp"
