target(pco-controller)

append(pco-controller_SOURCES
    pco-controller.cpp
    pco-controller.h

    pco-controller_PcoModel.cpp
    pco-controller_PcoModel.hpp
    pco-controller_PcoModel.h
)

append(pco-controller_PUBLIC_DEPS
    pco-core
)

build_avr_library(pco-controller)

