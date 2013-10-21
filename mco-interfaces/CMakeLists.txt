target(mco-interfaces)

append(mco-interfaces_SOURCES
    mco-interfaces.cpp
    mco-interfaces.h
    
    interfaces/mco-interfaces_Modulation.cpp
    interfaces/mco-interfaces_Modulation.hpp
    interfaces/mco-interfaces_Modulation.h
    #interfaces/mco-interfaces_Slope.cpp
    #interfaces/mco-interfaces_Slope.hpp
    #interfaces/mco-interfaces_Slope.h
    interfaces/mco-interfaces_SPI.cpp
    interfaces/mco-interfaces_SPI.hpp
    interfaces/mco-interfaces_SPI.h
)

append(mco-interfaces_PUBLIC_DEPS
    mco-core
)

build_avr_library(mco-interfaces)

