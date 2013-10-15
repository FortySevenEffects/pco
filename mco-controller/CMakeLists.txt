target(mco-controller)

append(mco-controller_SOURCES
    mco-controller.cpp
    mco-controller.h

    mco-controller_McoModel.cpp
    mco-controller_McoModel.hpp
    mco-controller_McoModel.h
)

append(mco-controller_PUBLIC_DEPS
    mco-core
)

build_avr_library(mco-controller)

