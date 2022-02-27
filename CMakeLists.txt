# CMakeList.txt : CMake project for CMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)
project(BazCryptLIB VERSION 1.0.1 DESCRIPTION "BazCrypt Encryption Library")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(CTest)

add_subdirectory(BazCryptLIB)
configure_file(BazCryptLIB.pc.in BazCryptLIB.pc @ONLY)
add_subdirectory(BazCryptCLI)
install(FILES ${CMAKE_BINARY_DIR}/BazCryptLIB.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
add_subdirectory(TestLib)
