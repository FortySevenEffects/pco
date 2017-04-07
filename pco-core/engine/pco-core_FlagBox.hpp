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
