# CMakeList.txt : CMake project for CMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(GNUInstallDirs)

include(FetchContent)
FetchContent_Declare(
  BazPO
  GIT_REPOSITORY https://github.com/karusb/BazPO.git
  GIT_TAG        v0.2.0
)

FetchContent_MakeAvailable(BazPO)
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
add_executable(bazcrypt BazCryptCLI.cpp)

target_link_libraries(bazcrypt PUBLIC BazCryptLIB BazPO)

target_include_directories(bazcrypt PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/BazCryptLIB"
                          "${CMAKE_INSTALL_LIBDIR}"
                          )
install(TARGETS bazcrypt
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
