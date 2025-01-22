cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(plotpp CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example plotpp::plotpp)

message(STATUS "CONAN_INCLUDE_DIRS: ${CONAN_INCLUDE_DIRS}")
message(STATUS "CONAN_LIB_DIRS: ${CONAN_LIB_DIRS}")