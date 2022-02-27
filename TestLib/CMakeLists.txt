# CMakeList.txt : CMake project for CMake, include source and define

cmake_minimum_required (VERSION 3.14)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/bin)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
# Test Files
set_target_properties(BazCryptLIB PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/test/bin
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/test/bin
)
set_target_properties(bazcrypt PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/test/bin
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/test/bin
)
configure_file(small.txt ${CMAKE_BINARY_DIR}/test/bin/small.txt COPYONLY)
configure_file(bwbg.png ${CMAKE_BINARY_DIR}/test/bin/bwbg.png COPYONLY)

enable_testing()

add_executable(
  BazCryptCliTest
  CLITest.cpp
)

add_executable(
  BazCryptLibTest
  LIBTest.cpp
)

target_link_libraries(
  BazCryptCliTest
  gtest_main
  BazCryptLIB
)

target_link_libraries(
  BazCryptLibTest
  gtest_main
  BazCryptLIB
)

gtest_discover_tests(BazCryptCliTest)
gtest_discover_tests(BazCryptLibTest)