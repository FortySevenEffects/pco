#pragma once

#include "pco-core.h"
#include "pco-core_Defs.h"
#include <avr/io.h>

BEGIN_PCO_CORE_NAMESPACE

struct Flags
{
    enum
    {
        // Flags for General Purpose Register 0

          ClockRefresh          = 0
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

END_PCO_CORE_NAMESPACE

#include "engine/pco-core_FlagBox.hpp"
