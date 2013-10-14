target(mco-firmware)

append(mco-firmware_SOURCES
    mco-firmware.cpp
    mco-firmware.h
    mco-firmware_Main.cpp
    mco-firmware_Main.h
    mco-firmware_Engine.cpp
    mco-firmware_Engine.hpp
    mco-firmware_Engine.h

    core/mco-firmware_PinMapping.h
    core/mco-firmware_PinMapping_t84.h
    core/mco-firmware_Settings.h
    
    interfaces/mco-firmware_Modulation.cpp
    interfaces/mco-firmware_Modulation.hpp
    interfaces/mco-firmware_Modulation.h
    interfaces/mco-firmware_Slope.cpp
    interfaces/mco-firmware_Slope.hpp
    interfaces/mco-firmware_Slope.h
    interfaces/mco-firmware_SPI.cpp
    interfaces/mco-firmware_SPI.hpp
    interfaces/mco-firmware_SPI.h
    interfaces/mco-firmware_Sync.cpp
    interfaces/mco-firmware_Sync.hpp
    interfaces/mco-firmware_Sync.h
)

append(mco-firmware_PUBLIC_DEPS
    mco-core
)

build_avr_firmware(mco-firmware)

