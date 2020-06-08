cmake_minimum_required(VERSION 3.11.0)

####################################
# Add Main Project
file(
    GLOB_RECURSE
    source_list
    RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "source/*"
)

add_executable( ULIS3_WASM ${source_list} )
set( CMAKE_EXECUTABLE_SUFFIX ".html" )
