/*!
 *  \file       pco-core_FlagBox.hpp
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

BEGIN_PCO_CORE_NAMESPACE

template<flagbox::Flag inFlag>
inline bool flagbox::isSet()
{
    return GPIOR0 & (1 << inFlag);
}

template<flagbox::Flag inFlag>
inline void flagbox::set()
{
    GPIOR0 |= (1 << inFlag);
}

template<flagbox::Flag inFlag>
inline void flagbox::clear()
{
    GPIOR0 &= ~(1 << inFlag);
}

END_PCO_CORE_NAMESPACE
