cmake_minimum_required(VERSION 3.18.0)

# project building process: 
set(PROJECT_NAME plotplusplus)
project(${PROJECT_NAME})

# Basic compiler settings
message(STATUS "======================== Fetching External Libraries =========================")

find_package(Gnuplot 5.4.4)
add_subdirectory(opstream)

message(STATUS "======================== END: Fetching External Libraries =========================")

# define the library
add_library(plotpp STATIC
	plotpp/Text.cpp
	plotpp/Figure.cpp
	plotpp/ArrowHeadStyle.cpp
	plotpp/ImageFileType.cpp
	plotpp/LineType.cpp
	plotpp/OutputFileType.cpp
	plotpp/TerminalType.cpp
)

target_include_directories(plotpp PUBLIC
	.
)

target_compile_features(plotpp PUBLIC cxx_std_20)

target_link_libraries(plotpp PUBLIC
	opstream
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
			
			# Enable link time optimisations
			-flto
			
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
	target_link_libraries(line PUBLIC plotpp)
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
endif()





