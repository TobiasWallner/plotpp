if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(COMPILER_FLAGS 
		$<$<CONFIG:Debug>: -Og -g>
		$<$<CONFIG:Release>: -O2>
	)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(COMPILER_FLAGS
		-fconcepts-diagnostics-depth=2
		$<$<CONFIG:Debug>: -Og -g -ggdb>
		$<$<CONFIG:Release>: -O2>
	)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(COMPILER_FLAGS
		/W3 /Zc:__cplusplus 
		$<$<CONFIG:Debug>: /Od /ZI>
		$<$<CONFIG:Release>: /O2>
	)
else()
	message(SEND_ERROR "The compiler you are using is not handeled. Add your compiler and compiler flags to the if(CMAKE_CXX_COMPILER_ID STREQUAL <your compiler>) in the CMakeLists.txt of the root folder")
endif()

# List of examples
set(EXAMPLES
    boxes
    line
    points
    heatmap
    mixed_plot
    arrows
    multiplot
    xerror
    yerror
    xyerror
    color
    boxplot
    logscale
    circle
    piechart
    filledline
    filledcurves
    impulses
    steps
)

# Add each example executable
foreach(EXAMPLE ${EXAMPLES})
    add_executable(${EXAMPLE} "${EXAMPLE}.cpp")
    target_link_libraries(${EXAMPLE} PUBLIC plotpp)
    target_compile_options(${EXAMPLE} PUBLIC ${COMPILER_FLAGS})
endforeach()
