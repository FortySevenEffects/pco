target(pco-core)

append(pco-core_SOURCES
    pco-core.cpp
    pco-core.h
    pco-core_Defs.cpp
    pco-core_Defs.h

    engine/pco-core_Engine.cpp
    engine/pco-core_Engine.hpp
    engine/pco-core_Engine.h
    engine/pco-core_Math.cpp
    engine/pco-core_Math.hpp
    engine/pco-core_Math.h
    engine/pco-core_Tables.cpp
    engine/pco-core_Tables.h
    engine/pco-core_Timer.cpp
    engine/pco-core_Timer.hpp
    engine/pco-core_Timer.h
    engine/pco-core_Pitch.cpp
    engine/pco-core_Pitch.hpp
    engine/pco-core_Pitch.h
    engine/pco-core_TickCounter.cpp
    engine/pco-core_TickCounter.hpp
    engine/pco-core_TickCounter.h
    engine/pco-core_Mappers.cpp
    engine/pco-core_Mappers.hpp
    engine/pco-core_Mappers.h

    modules/pco-core_Portamento.cpp
    modules/pco-core_Portamento.hpp
    modules/pco-core_Portamento.h
    modules/pco-core_LFO.cpp
    modules/pco-core_LFO.hpp
    modules/pco-core_LFO.h
    modules/pco-core_Envelope.cpp
    modules/pco-core_Envelope.hpp
    modules/pco-core_Envelope.h
    modules/pco-core_Vibrato.cpp
    modules/pco-core_Vibrato.hpp
    modules/pco-core_Vibrato.h
    modules/pco-core_PWM.cpp
    modules/pco-core_PWM.hpp
    modules/pco-core_PWM.h
    modules/pco-core_SlowRandom.cpp
    modules/pco-core_SlowRandom.hpp
    modules/pco-core_SlowRandom.h
    modules/pco-core_Twang.cpp
    modules/pco-core_Twang.hpp
    modules/pco-core_Twang.h
    modules/pco-core_Tuning.cpp
    modules/pco-core_Tuning.hpp
    modules/pco-core_Tuning.h
)

append(pco-core_PUBLIC_DEPS
    cake
    pco-common
)

build_avr_library(pco-core)

