cmake_minimum_required(VERSION 3.11.0)

# Set Cache variables
SET( ULIS_USE_CONFIG                       OFF         CACHE BOOL      "Scpecifies wether to use config files for overriding cache variables" )
SET( ULIS_BOOST_INCLUDE_PATH               "unset"     CACHE STRING    "Indicates the path to boost include dir" )
SET( ULIS_COAL_INCLUDE_PATH                "unset"     CACHE STRING    "Indicates the path to coal include dir" )
SET( ULIS_BUILD_SHARED                     OFF         CACHE BOOL      "Sets if we build the library shared or static" )
SET( ULIS_BUILD_TESTS                      ON          CACHE BOOL      "Sets if we build the test programs" )

SET( IS_VISUALSTUDIO_SOLUTION_MSVC  OFF )
SET( IS_MINGW_MAKEFILE_GCC          OFF )

if( ${CMAKE_GENERATOR} STREQUAL "Visual Studio 15 2017 Win64" )
    SET( IS_VISUALSTUDIO_SOLUTION_MSVC  ON )
endif()

if( ${CMAKE_GENERATOR} STREQUAL "MinGW Makefiles" )
    SET( IS_MINGW_MAKEFILE_GCC          ON )
endif()

# Generate only Debug and Release configurations for all projects
set( CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )
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

# Read Preferences if needed
if( ${ULIS_USE_CONFIG} )
    # Read Default Preferences
    include(${CMAKE_CURRENT_SOURCE_DIR}/../Tools/DefaultConfig.cmake)
    # Read Preferences Overrides if set
    # For VisualStudio
    if( ${IS_VISUALSTUDIO_SOLUTION_MSVC} )
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../VisualStudio_Solution_MSVC_Config.cmake)
            include(${CMAKE_CURRENT_SOURCE_DIR}/../../VisualStudio_Solution_MSVC_Config.cmake)
        endif()
    endif()
    # For MinGW
    if( ${IS_MINGW_MAKEFILE_GCC} )
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../MinGW_Makefile_GCC_Config.cmake)
            include(${CMAKE_CURRENT_SOURCE_DIR}/../../MinGW_Makefile_GCC_Config.cmake)
        endif()
    endif()
endif()

# Add projects
include(${CMAKE_CURRENT_SOURCE_DIR}/ULIS/CMakeLists.txt)

if( ${ULIS_BUILD_TESTS} )
    include(${CMAKE_CURRENT_SOURCE_DIR}/ULIS_Test/CMakeLists.txt) # Depends on ULIS
endif()

set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ULIS )
