target(pco-interfaces)

append(pco-interfaces_SOURCES
    pco-interfaces.cpp
    pco-interfaces.h

    interfaces/pco-interfaces_Modulation.cpp
    interfaces/pco-interfaces_Modulation.hpp
    interfaces/pco-interfaces_Modulation.h
    #interfaces/pco-interfaces_Slope.cpp
    #interfaces/pco-interfaces_Slope.hpp
    #interfaces/pco-interfaces_Slope.h
    interfaces/pco-interfaces_SPI.cpp
    interfaces/pco-interfaces_SPI.hpp
    interfaces/pco-interfaces_SPI.h
)

append(pco-interfaces_PUBLIC_DEPS
    pco-core
)

build_avr_library(pco-interfaces)

