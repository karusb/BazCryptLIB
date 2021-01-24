# CMakeList.txt : CMake project for CMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(BazCryptLIB VERSION 1.0.0 DESCRIPTION "BazCrypt Encryption Library")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(GNUInstallDirs)
# Add source to this project's executable.
add_library(BazCryptLIB SHARED
    BazCryptLIB/BazCryptLIB.cpp
    BazCryptLIB/BazCryptLIB.h
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


    # use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
add_executable(bazcrypt BazCryptCLI.cpp)

target_link_libraries(bazcrypt PUBLIC BazCryptLIB)


target_include_directories(bazcrypt PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/BazCryptLIB"
                          "${CMAKE_INSTALL_LIBDIR}"
                          )
install(TARGETS bazcrypt
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


# TODO: Add tests.
