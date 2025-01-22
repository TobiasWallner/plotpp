cmake_minimum_required(VERSION 3.18.0) 

# project building process: 
project(plotpp LANGUAGES CXX VERSION 0.1)

# -----------------------------------------------------------------
# 					Add Modules / Dependencies
# -----------------------------------------------------------------

message(STATUS "Searching for Gnuplot >= 5.4")
find_package(Gnuplot 5.4)
if(Gnuplot_FOUND)
    message(STATUS "  found Gnuplot")
else()
    message(WARNING "  Gnuplot >= 5.4.4 not found!\n"
                    "    Gnuplot installation instructions:\n"
                    "    - On Ubuntu/Debian: sudo apt update && sudo apt install gnuplot\n"
                    "    - On Fedora: sudo dnf install gnuplot\n"
                    "    - On macOS (with Homebrew): brew install gnuplot\n"
                    "    - On Windows: Download the installer from https://sourceforge.net/projects/gnuplot/\n"
	                "    You will still be able to compile your project but it will not be able to talk to gnuplot and plot figures")
endif()

find_package(fmt REQUIRED)

# ------------------------------------------------------------------------------------------
# 					Add source files, link dependencies, set compiler options
# ------------------------------------------------------------------------------------------

# Collect all .hpp files in the plotpp directory
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/plotpp/*.hpp")
set(MAIN_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/plotpp.hpp")

# Collect all .cpp files in the plotpp directory
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/plotpp/*.cpp")

# define the library source files
add_library(plotpp STATIC ${SOURCE_FILES})

set_target_properties(plotpp PROPERTIES PUBLIC_HEADER "${MAIN_HEADER}")

# add OS specific definitions
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(plotpp PRIVATE -DWIN32)
endif()

# include directories
target_include_directories(plotpp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# define the language standard needed
target_compile_features(plotpp PUBLIC cxx_std_20)

# link libraries
target_link_libraries(plotpp PUBLIC fmt::fmt)

# install libraries
install(TARGETS plotpp
    ARCHIVE DESTINATION lib)
	
# install main-header file
install(FILES "${MAIN_HEADER}" DESTINATION include)
	
# install other-header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/plotpp/
        DESTINATION include/plotpp
        FILES_MATCHING PATTERN "*.hpp")


# --------------------------------------------------------------------------
# 								Examples
# --------------------------------------------------------------------------

option(BUILD_EXAMPLES "Description of the feature" OFF)
if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()