cmake_minimum_required(VERSION 3.18.0)

# project building process: 
project(plotpp)

# -----------------------------------------------------------------
# 	CPM: An Awesome Dependency Manager for C++ with CMake
#		https://github.com/cpm-cmake/CPM.cmake
# -----------------------------------------------------------------

set(CPM_CMAKE_PATH "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
set(CPM_CMAKE_URL "https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.2/CPM.cmake")

# Check if CPM.cmake exists
if(NOT EXISTS "${CPM_CMAKE_PATH}")
    message(STATUS "CPM.cmake not found. Downloading from ${CPM_CMAKE_URL}...")
    file(DOWNLOAD ${CPM_CMAKE_URL} ${CPM_CMAKE_PATH} STATUS download_status LOG download_log)
    list(GET download_status 0 return_code)  # Get the numeric return code
	list(GET download_status 1 error_message)  # Get the error message
	if(return_code)
		file(REMOVE ${CPM_CMAKE_PATH}) #cleanup
		message(FATAL_ERROR 
			"Error: ${error_message}.\n"
			"    Failed to download CPM.cmake. Check the URL or download it manually and place it at:\n"
			"    ${CPM_CMAKE_PATH}")
	else()
		message(STATUS "Successfully downloaded CPM.cmake.")
    endif()
else()
    message(STATUS "Found CPM.cmake at ${CPM_CMAKE_PATH}.")
endif()


include(${CPM_CMAKE_PATH})
option(CPM_USE_LOCAL_PACKAGES "Try `find_package` before downloading dependencies" ON)

# -----------------------------------------------------------------
# 					Add Modules / Dependencies
# -----------------------------------------------------------------

message(STATUS "======================== Plotpp: Fetching External Libraries =========================")

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
 
add_subdirectory(opstream)

# {fmt}
# Github: https://github.com/fmtlib/fmt
# Documentation: https://fmt.dev/11.0/
CPMAddPackage("gh:fmtlib/fmt#11.0.2")

# zip-iterator
# Github: https://github.com/CommitThis/zip-iterator
#CPMAddPackage("gh:CommitThis/zip-iterator#master")
CPMAddPackage("gh:TobiasWallner/zip-iterator#256cd6247d447761c5b768ee2a6703335c66c605") # fork


message(STATUS "======================== Plotpp: END: Fetching External Libraries =========================")

# ------------------------------------------------------------------------------------------
# 					Add source files, link dependencies, set compiler options
# ------------------------------------------------------------------------------------------

# define the library
add_library(plotpp STATIC
	plotpp/Text.cpp
	plotpp/Circle.cpp
	plotpp/Figure.cpp
	plotpp/Multiplot.cpp
	plotpp/ArrowHeadStyle.cpp
	plotpp/ImageFileType.cpp
	plotpp/LineType.cpp
	plotpp/OutputFileType.cpp
	plotpp/TerminalType.cpp
)

target_include_directories(plotpp PUBLIC
	.
	optional_ptr
	${zip-iterator_SOURCE_DIR}
)

target_compile_features(plotpp PUBLIC cxx_std_20)

target_link_libraries(plotpp PUBLIC
	opstream
	fmt::fmt
)

# optionally build examples with `-DBUILD_EXAMPLES=ON`
# --------------------------------------------------------------------------

option(BUILD_EXAMPLES "Description of the feature" OFF)

if(BUILD_EXAMPLES)
	
	

	# Compiler Options for Clang:
	# ===========================
	if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
		set(COMPILER_FLAGS 
			
			# set compiler flags for debugging
			#---------------------------------
			$<$<CONFIG:Debug>:
				-O0	# disable optimisations
				-g	# enable debug information
			>
			
			# set compiler flags for release
			#-------------------------------
			$<$<CONFIG:Release>:
				-O2 # Enable all Optimisations
			>
		)
	# Compiler Options for GNU:
	# =========================
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		set(COMPILER_FLAGS
			-fconcepts-diagnostics-depth=3
			
			# set compiler flags for debugging
			#---------------------------------
			$<$<CONFIG:Debug>:
				-O0	# disable optimisations
				-g	# enable debug information
				-ggdb # extra flag for the debugger
			>
			
			# set compiler flags for release
			#-------------------------------
			$<$<CONFIG:Release>:
				-O2 # Enable all Optimisations
			>
		)
	# Compiler Options for MSVC:
	# ==========================
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		set(COMPILER_FLAGS
			/W3
			/Zc:__cplusplus # enable __cplusplus
			# set compiler flags for debugging
			#---------------------------------
			$<$<CONFIG:Debug>:
			
				# disable optimisations for debugging
				/Od 
				
				# produces a PDB file in a format that supports the Edit and Continue feature. 
				# To use Edit and Continue debugging features, you must use this option. 
				/ZI 
			>
			
			# set compiler flags for release versions
			#----------------------------------------
			$<$<CONFIG:Release>:
				
				# Creates fast code
				/O2 
			>
		)
	else()
		message(SEND_ERROR "The compiler you are using is not handeled. Add your compiler and compiler flags to the if(CMAKE_CXX_COMPILER_ID STREQUAL <your compiler>) in the CMakeLists.txt of the root folder")
	endif()

	# boxes
	add_executable(boxes examples/boxes.cpp)
	target_link_libraries(boxes PUBLIC plotpp)
	target_compile_options(boxes PUBLIC ${COMPILER_FLAGS})
	
	# line
	add_executable(line examples/line.cpp)
	target_link_libraries(line PUBLIC plotpp fmt::fmt)
	target_compile_options(line PUBLIC ${COMPILER_FLAGS})
	
	# line
	add_executable(points examples/points.cpp)
	target_link_libraries(points PUBLIC plotpp)
	target_compile_options(points PUBLIC ${COMPILER_FLAGS})
	
	# heatmap
	add_executable(heatmap examples/heatmap.cpp)
	target_link_libraries(heatmap PUBLIC plotpp)
	target_compile_options(heatmap PUBLIC ${COMPILER_FLAGS})
	
	# mixed_plot
	add_executable(mixed_plot examples/mixed_plot.cpp)
	target_link_libraries(mixed_plot PUBLIC plotpp)
	target_compile_options(mixed_plot PUBLIC ${COMPILER_FLAGS})
	
	# arrows
	add_executable(arrows examples/arrows.cpp)
	target_link_libraries(arrows PUBLIC plotpp)
	target_compile_options(arrows PUBLIC ${COMPILER_FLAGS})
	
	# multiplot
	add_executable(multiplot examples/multiplot.cpp)
	target_link_libraries(multiplot PUBLIC plotpp)
	target_compile_options(multiplot PUBLIC ${COMPILER_FLAGS})
	
	# xerror
	add_executable(xerror examples/xerror.cpp)
	target_link_libraries(xerror PUBLIC plotpp)
	target_compile_options(xerror PUBLIC ${COMPILER_FLAGS})
	
	# yerror
	add_executable(yerror examples/yerror.cpp)
	target_link_libraries(yerror PUBLIC plotpp)
	target_compile_options(yerror PUBLIC ${COMPILER_FLAGS})
	
	# xyerror
	add_executable(xyerror examples/xyerror.cpp)
	target_link_libraries(xyerror PUBLIC plotpp)
	target_compile_options(xyerror PUBLIC ${COMPILER_FLAGS})
	
	# color
	add_executable(color examples/color.cpp)
	target_link_libraries(color PUBLIC plotpp)
	target_compile_options(color PUBLIC ${COMPILER_FLAGS})
	
	# boxplot
	add_executable(boxplot examples/boxplot.cpp)
	target_link_libraries(boxplot PUBLIC plotpp)
	target_compile_options(boxplot PUBLIC ${COMPILER_FLAGS})
	
	# logscale
	add_executable(logscale examples/logscale.cpp)
	target_link_libraries(logscale PUBLIC plotpp)
	target_compile_options(logscale PUBLIC ${COMPILER_FLAGS})
	
	# circle
	add_executable(circle examples/circle.cpp)
	target_link_libraries(circle PUBLIC plotpp)
	target_compile_options(circle PUBLIC ${COMPILER_FLAGS})
	
	# piechart
	add_executable(piechart examples/piechart.cpp)
	target_link_libraries(piechart PUBLIC plotpp)
	target_compile_options(piechart PUBLIC ${COMPILER_FLAGS})
endif()





