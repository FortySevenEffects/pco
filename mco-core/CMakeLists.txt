target(mco-core)

append(mco-core_SOURCES
    mco-core.cpp
    mco-core.h
    mco-core_Defs.cpp
    mco-core_Defs.h
    
    engine/mco-core_Engine.cpp
    engine/mco-core_Engine.hpp
    engine/mco-core_Engine.h
    engine/mco-core_Math.cpp
    engine/mco-core_Math.hpp
    engine/mco-core_Math.h
    engine/mco-core_Tables.cpp
    engine/mco-core_Tables.h
    engine/mco-core_Timer.cpp
    engine/mco-core_Timer.hpp
    engine/mco-core_Timer.h
    engine/mco-core_Pitch.cpp
    engine/mco-core_Pitch.hpp
    engine/mco-core_Pitch.h
    engine/mco-core_TickCounter.cpp
    engine/mco-core_TickCounter.hpp
    engine/mco-core_TickCounter.h
    engine/mco-core_Mappers.cpp
    engine/mco-core_Mappers.hpp
    engine/mco-core_Mappers.h

    modules/mco-core_Portamento.cpp
    modules/mco-core_Portamento.hpp
    modules/mco-core_Portamento.h
    modules/mco-core_LFO.cpp
    modules/mco-core_LFO.hpp
    modules/mco-core_LFO.h
    modules/mco-core_Envelope.cpp
    modules/mco-core_Envelope.hpp
    modules/mco-core_Envelope.h
    modules/mco-core_Vibrato.cpp
    modules/mco-core_Vibrato.hpp
    modules/mco-core_Vibrato.h
    modules/mco-core_PWM.cpp
    modules/mco-core_PWM.hpp
    modules/mco-core_PWM.h
    modules/mco-core_SlowRandom.cpp
    modules/mco-core_SlowRandom.hpp
    modules/mco-core_SlowRandom.h
    modules/mco-core_Twang.cpp
    modules/mco-core_Twang.hpp
    modules/mco-core_Twang.h
    modules/mco-core_Tuning.cpp
    modules/mco-core_Tuning.hpp
    modules/mco-core_Tuning.h
)

append(mco-core_PUBLIC_DEPS
    ak47
    mco-common
)

build_avr_library(mco-core)

