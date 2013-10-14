target(mco-interfaces)

append(mco-interfaces_SOURCES
    mco-interfaces.cpp
    mco-interfaces.h
    mco-interfaces_Main.cpp
    mco-interfaces_Main.h
    mco-interfaces_Engine.cpp
    mco-interfaces_Engine.hpp
    mco-interfaces_Engine.h

    core/mco-interfaces_PinMapping.h
    core/mco-interfaces_PinMapping_t84.h
    core/mco-interfaces_Settings.h
    
    interfaces/mco-interfaces_Modulation.cpp
    interfaces/mco-interfaces_Modulation.hpp
    interfaces/mco-interfaces_Modulation.h
    interfaces/mco-interfaces_Slope.cpp
    interfaces/mco-interfaces_Slope.hpp
    interfaces/mco-interfaces_Slope.h
    interfaces/mco-interfaces_SPI.cpp
    interfaces/mco-interfaces_SPI.hpp
    interfaces/mco-interfaces_SPI.h
    interfaces/mco-interfaces_Sync.cpp
    interfaces/mco-interfaces_Sync.hpp
    interfaces/mco-interfaces_Sync.h
)

append(mco-interfaces_PUBLIC_DEPS
    mco-core
)

build_avr_interfaces(mco-interfaces)

