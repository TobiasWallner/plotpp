cmake_minimum_required(VERSION 3.18.0)

set (CMAKE_CXX_STANDARD 20)

# define the library
add_library(opstream STATIC
	opstream.cpp opstream.hpp 
)

target_include_directories(opstream PUBLIC
	.
)

target_compile_features(opstream PUBLIC cxx_std_20)

# add OS specific definitions
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(opstream PRIVATE -DWIN32)
endif()



