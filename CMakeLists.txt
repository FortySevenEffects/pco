add_subdirectory(mco-common)
add_subdirectory(mco-core)

if(AVR_MCU STREQUAL "attiny84")
    add_subdirectory(mco-firmware)
endif()
