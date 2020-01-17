cmake_minimum_required(VERSION 3.11.0)

option( ULIS2_BUILD_SHARED "Build the library shared or statically" OFF )
SET( ULIS2_QT_CMAKE_PATH "default" CACHE STRING "Indicates the path to Qt cmake package" )

# Display host & compiler
message( "Generating: ${CMAKE_HOST_SYSTEM_NAME} ${CMAKE_CXX_COMPILER_ID}" )

# Set OSX version target
set( CMAKE_OSX_DEPLOYMENT_TARGET "10.13" )

# Generate only Debug and Release configurations
set( CMAKE_CONFIGURATION_TYPES Debug Release CACHE STRING INTERNAL FORCE )

# Get rid of cmake's ZERO_CHECK project
set( CMAKE_SUPPRESS_REGENERATION true )

# Set Debug postfix
set( CMAKE_DEBUG_POSTFIX d )

# Set C++ standard options
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )
if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
	set( CMAKE_CXX_FLAGS "-std=c++14" )
endif()

# Create global solution
project( ULIS2 )

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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Z7 -MP -Od -MDd")
    # Z7: Produced object files contain full symbolic debugging information.
    # MP: Parallelize compilation of source files.
    # Od: Turns off all optimizations in the program and speeds compilation.
endif()

# Add Dependencies
include(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/Little-CMS/CMakeLists.txt)

####################################
# Add Main Project
file(
    GLOB_RECURSE
    source_list
    RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "include/*"
    "source/*"
)

if( ${ULIS2_BUILD_SHARED} )
   add_library( ULIS2 SHARED ${source_list} )
   target_compile_definitions( ULIS2 PUBLIC ULIS2_BUILD_SHARED )
else()
   add_library( ULIS2 STATIC ${source_list} )
   target_compile_definitions( ULIS2 PUBLIC ULIS2_BUILD_STATIC )
endif()

target_compile_definitions( ULIS2 PUBLIC UNICODE )
find_package(OpenCL REQUIRED)
set_target_properties( ULIS2 PROPERTIES OUTPUT_NAME "ULIS2.0" )
target_link_libraries( ULIS2 PUBLIC lcms2 )
target_link_libraries( ULIS2 PUBLIC ${OpenCL_LIBRARY} )

target_include_directories(
    ULIS2
    PUBLIC
    "include/"
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/Little-CMS/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm/
    ${OpenCL_INCLUDE_DIR}
    PRIVATE
    "source/"
)

# For MSVC parse pretty filter names
foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

####################################
# Add Test Project
file(
    GLOB_RECURSE
    source_list
    RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "test.cpp"
)

add_executable( Test ${source_list} )
target_link_libraries( Test ULIS2 )

# For MSVC parse pretty filter names
foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

####################################
# Add GUI Project
# Qt Options
if( NOT "${ULIS2_QT_CMAKE_PATH}" STREQUAL "default")
    set( CMAKE_PREFIX_PATH ${ULIS2_QT_CMAKE_PATH} )

    find_package(
        Qt5
        REQUIRED COMPONENTS
        Core
        Widgets
        Gui
    )

    file(
        GLOB_RECURSE
        source_list
        RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "gui.cpp"
    )

    add_executable( Gui ${source_list} )
    set_target_properties( Gui PROPERTIES CMAKE_AUTOMOC ON )
    target_link_libraries(
        Gui
        ULIS2
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
    )

    # For MSVC parse pretty filter names
    foreach(source IN LISTS source_list)
        get_filename_component(source_path "${source}" PATH)
        string(REPLACE "/" "\\" source_path_msvc "${source_path}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()

endif()

# Set default startup project
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Test )
