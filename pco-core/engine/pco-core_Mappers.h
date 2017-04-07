/*!
 *  \file       pco-core_Mappers.h
 *  \author     Francois Best
 *  \date       27/10/2013
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

#include "pco-core.h"
#include "pco-core_Defs.h"

BEGIN_PCO_CORE_NAMESPACE

template<typename Type, Type Min, Type Max>
struct LinearMapper
{
    static inline Type map(Amount inAmount);
};

END_PCO_CORE_NAMESPACE

#include "engine/pco-core_Mappers.hpp"
