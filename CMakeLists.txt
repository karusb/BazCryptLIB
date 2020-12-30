# CMakeList.txt : CMake project for CMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(BazCryptLIB VERSION 1.0.0 DESCRIPTION "BazCrypt Encryption Library")
include(GNUInstallDirs)
# Add source to this project's executable.
add_library(BazCryptLIB SHARED
    BazCryptLIB/BazCryptLIB.cpp
)
set_target_properties(BazCryptLIB PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER BazCryptLIB/BazCryptLIB.h)
configure_file(BazCryptLIB.pc.in BazCryptLIB.pc @ONLY)
#target_include_directories(BazCryptLIB PRIVATE .)
install(TARGETS BazCryptLIB
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/BazCryptLIB.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
# TODO: Add tests.
