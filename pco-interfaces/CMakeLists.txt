target(pco-interfaces)

target_sources(pco-interfaces
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

target_deps(pco-interfaces
    pco-core
)

build_avr_library(pco-interfaces)
