target(pco-controller)

target_sources(pco-controller
    pco-controller.cpp
    pco-controller.h

    pco-controller_PcoModel.cpp
    pco-controller_PcoModel.hpp
    pco-controller_PcoModel.h
)

target_deps(pco-controller
    pco-core
)

build_static_library(pco-controller)

