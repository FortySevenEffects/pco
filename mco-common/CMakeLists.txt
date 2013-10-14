target(mco-common)

append(mco-common_SOURCES
    mco-common.cpp
    mco-common.h
    mco-common_Messages.cpp
    mco-common_Messages.h
)

build_avr_library(mco-common)

