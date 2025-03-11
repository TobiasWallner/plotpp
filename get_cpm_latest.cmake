# -----------------------------------------------------------------
# 	CPM: An Awesome Dependency Manager for C++ with CMake
#		https://github.com/cpm-cmake/CPM.cmake
# -----------------------------------------------------------------

set(CPM_CMAKE_PATH "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
set(CPM_CMAKE_URL "https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake")

# Check if CPM.cmake exists
if(NOT EXISTS "${CPM_CMAKE_PATH}")
	
	# download the CPM.cmake file
    message(STATUS "CPM.cmake not found. Downloading from ${CPM_CMAKE_URL}...")
    file(DOWNLOAD ${CPM_CMAKE_URL} ${CPM_CMAKE_PATH} STATUS download_status LOG download_log)
    
	# manage errors during download
	list(GET download_status 0 return_code)
	list(GET download_status 1 error_message)
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

# include cpm
include(${CPM_CMAKE_PATH})