cmake_minimum_required(VERSION 3.18.0)

# define the library
add_library(opstream STATIC
	opstream.cpp 
)

target_include_directories(opstream PUBLIC
	.
)

# add OS specific definitions
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(opstream PRIVATE -DWIN32)
endif()



