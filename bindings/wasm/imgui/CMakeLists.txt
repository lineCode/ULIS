cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wno-missing-braces")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -s USE_SDL=2 -std=c++1z")
include_directories(src)
include_directories( SYSTEM external ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} )

file( GLOB_RECURSE wimgui_source_list RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "external/*" "src/*" )
add_executable( wimgui ${wimgui_source_list} )

set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++17")

target_link_libraries( wimgui ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} )
