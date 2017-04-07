target(pco-common)

append(pco-common_SOURCES
    pco-common.cpp
    pco-common.h
    pco-common_Messages.cpp
    pco-common_Messages.h
)

build_avr_library(pco-common)
