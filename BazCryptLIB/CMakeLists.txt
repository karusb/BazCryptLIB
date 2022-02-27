# CMakeList.txt : CMake project for CMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(GNUInstallDirs)
if (UNIX)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif (UNIX)

if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
endif (MSVC)
# Add source to this project's executable.
add_library(BazCryptLIB SHARED
    BazCryptLIB.cpp
    BazCryptLIB.h
)
set_target_properties(BazCryptLIB PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER BazCryptLIB.h)

install(TARGETS BazCryptLIB
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

