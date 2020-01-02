cmake_minimum_required(VERSION 3.11.0)

# Set Cache variables
SET( ULIS2_GLM_INCLUDE_PATH         "unset"     CACHE STRING    "Indicates the path to glm include dir" )
SET( ULIS2_LCMS2_INCLUDE_PATH       "unset"     CACHE STRING    "Indicates the path to lcms2 include dir" )
SET( ULIS2_LCMS2_DEBUG_LIB_PATH     "unset"     CACHE STRING    "Indicates the path to lcms2 debug lib" )
SET( ULIS2_LCMS2_RELEASE_LIB_PATH   "unset"     CACHE STRING    "Indicates the path to lcms2 release lib" )
SET( ULIS2_VERSION_MAJOR            "unset"     CACHE STRING    "Indicate ULIS version major" )
SET( ULIS2_VERSION_MINOR            "unset"     CACHE STRING    "Indicate ULIS version minor" )

# Display host & compiler
message( "Generating: ${CMAKE_HOST_SYSTEM_NAME} ${CMAKE_CXX_COMPILER_ID}")

# Set OSX version target
set( CMAKE_OSX_DEPLOYMENT_TARGET "10.13" )

# Generate only Debug and Release configurations
set( CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE )

# Get rid of cmake's ZERO_CHECK project
set( CMAKE_SUPPRESS_REGENERATION true )

# Set Debug postfix
set( CMAKE_DEBUG_POSTFIX d )

# Set C++ standard options
set( CMAKE_CXX_FLAGS "-std=c++14" )
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Create global solution
project( ULIS2 CXX )

# Check Endianness
include( TestBigEndian )
TEST_BIG_ENDIAN( IS_BIG_ENDIAN )
if( IS_BIG_ENDIAN )
    message( STATUS "BIG_ENDIAN" )
else()
    message( STATUS "LITTLE_ENDIAN" )
endif()

# Flags for Compiler / Platforms
if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    if( "${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Linux" )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1 -W -pthread")
    elseif( "${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Windows" )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1 -Wa")
    endif()
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Z7 -MP -Od -MDd")
    # Z7: Produced object files contain full symbolic debugging information.
    # MP: Parallelize compilation of source files.
    # Od: Turns off all optimizations in the program and speeds compilation.
endif()

# Add project
file(
    GLOB_RECURSE
    source_list
    RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "include/*"
    "source/*"
)

add_library( ULIS2 ${source_list} )

target_compile_definitions( ULIS2 PUBLIC UNICODE )
set_target_properties( ULIS2 PROPERTIES OUTPUT_NAME "ULIS2.0" )

target_link_libraries(
    ULIS2
    PUBLIC
    debug ${ULIS2_LCMS2_DEBUG_LIB_PATH}
    optimized ${ULIS2_LCMS2_RELEASE_LIB_PATH}
)

target_include_directories(
    ULIS2
    PUBLIC
    "include/"
    ${ULIS2_GLM_INCLUDE_PATH}
    ${ULIS2_LCMS2_INCLUDE_PATH}
    PRIVATE
    "source/"
)

# For MSVC parse pretty filter names
foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

# Set default startup project
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ULIS2 )
