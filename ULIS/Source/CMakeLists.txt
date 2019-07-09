cmake_minimum_required(VERSION 3.11.0)

# Set Cache variables
SET( ULIS_EXPLICIT_COMPILER_ID             "unset"     CACHE STRING    "Explicitly set compiler ID from command line" )
SET( ULIS_USE_CONFIG                       OFF         CACHE BOOL      "Scpecifies wether to use config files for overriding cache variables" )
SET( ULIS_BOOST_INCLUDE_PATH               "unset"     CACHE STRING    "Indicates the path to boost include dir" )
SET( ULIS_COAL_INCLUDE_PATH                "unset"     CACHE STRING    "Indicates the path to coal include dir" )
SET( ULIS_BUILD_SHARED                     OFF         CACHE BOOL      "Sets if we build the library shared or static" )
SET( ULIS_BUILD_TESTS                      OFF         CACHE BOOL      "Sets if we build the test programs" )
SET( ULIS_BUILD_GUIS                       OFF         CACHE BOOL      "Sets if we build the gui programs" )
SET( ULIS_QT_CMAKE_PATH                	   "unset"     CACHE STRING    "Indicates the path to Qt cmake package" )
SET( ULIS_GLM_INCLUDE_PATH                 "unset"     CACHE STRING    "Indicates the path to glm include dir" )

# Generate only Debug and Release configurations for all projects
set( CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE )
# Generate only x64 configurations for all projects
#set( CMAKE_GENERATOR_PLATFORM x64 )
# Get rid of cmake's ZERO_CHECK for solution
set( CMAKE_SUPPRESS_REGENERATION true )
# Set Debug postfix for all projects
set( CMAKE_DEBUG_POSTFIX d )
# Set Runtime Library for all projects
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
# Set C++ standard
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create global solution
project( ULIS CXX )

message( ${ULIS_EXPLICIT_COMPILER_ID} )
if( "${ULIS_EXPLICIT_COMPILER_ID}" STREQUAL "CLANG" )
	# CLANG
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
	
elseif( "${ULIS_EXPLICIT_COMPILER_ID}" STREQUAL "GCC" )
	# GCC
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
	message( "Additional flags for GCC ( Debug & Release ): -Wa,-mbig-obj" )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
	
	# Support for alternat drop-in replacement of ld linker with Clang's lld, only for recent GCC ( not 7.3.0 shipped with Qt )
	#set(CMAKE_LINKER lld)
	#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fuse-ld=lld")
	#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
	
elseif( "${ULIS_EXPLICIT_COMPILER_ID}" STREQUAL "MSVC" )
	# MSVC
	message( "Additional flags for MSVC ( Debug only ): -bigobj -Zi -Gm- -Od -Ob0 -RTC1 -MDd" )
	message( "Additional flags for MSVC ( Debug / Release ): -EHsc" )
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -bigobj -Zi -Gm- -Od -Ob0 -RTC1 -MDd -EHsc")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -EHsc")
	
endif()

# Read Preferences if needed
if( ${ULIS_USE_CONFIG} )
    # Read Default Preferences
    include(${CMAKE_CURRENT_SOURCE_DIR}/../Tools/DefaultConfig.cmake)
    # Read Preferences Overrides if set
	
	if( ${CMAKE_GENERATOR} STREQUAL "Xcode" )
		message( "OK LOADED FOR APPLE" )
		if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../Xcode_Config.cmake)
				include(${CMAKE_CURRENT_SOURCE_DIR}/../../Xcode_Config.cmake)
		endif()
	endif()
	
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		# using Clang
		if( ${CMAKE_GENERATOR} STREQUAL "Visual Studio 15 2017 Win64" )
			if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../VisualStudio_Solution_CLANG_LLVM_Config.cmake)
				include(${CMAKE_CURRENT_SOURCE_DIR}/../../VisualStudio_Solution_CLANG_LLVM_Config.cmake)
			endif()
		endif()
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		# using GCC
		if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../MinGW_Makefile_GCC_Config.cmake)
			include(${CMAKE_CURRENT_SOURCE_DIR}/../../MinGW_Makefile_GCC_Config.cmake)
		endif()
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
		# using Intel C++
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
		# using Visual Studio C++
		if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../VisualStudio_Solution_MSVC_Config.cmake)
			include(${CMAKE_CURRENT_SOURCE_DIR}/../../VisualStudio_Solution_MSVC_Config.cmake)
		endif()
	endif()
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	# using Clang
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	# using GCC
	set (CMAKE_PREFIX_PATH ${ULIS_QT_CMAKE_PATH})
	set (CMAKE_AUTOMOC ON)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	# using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# using Visual Studio C++
	set (CMAKE_PREFIX_PATH ${ULIS_QT_CMAKE_PATH})
	set (CMAKE_AUTOMOC ON)
endif()

# Add projects
include(${CMAKE_CURRENT_SOURCE_DIR}/ULIS/CMakeLists.txt)

if( ${ULIS_BUILD_TESTS} )
    include(${CMAKE_CURRENT_SOURCE_DIR}/ULIS_Test/CMakeLists.txt) # Depends on ULIS
    include(${CMAKE_CURRENT_SOURCE_DIR}/ULIS_Test_SSE/CMakeLists.txt) # Depends on ULIS
    include(${CMAKE_CURRENT_SOURCE_DIR}/ULIS_Test_Thread/CMakeLists.txt) # Depends on ULIS
endif()

if( ${ULIS_BUILD_GUIS} )
    include(${CMAKE_CURRENT_SOURCE_DIR}/ULIS_GUI/CMakeLists.txt) # Depends on ULIS
endif()

set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ULIS )
