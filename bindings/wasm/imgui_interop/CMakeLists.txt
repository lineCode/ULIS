cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wno-missing-braces")

if(${EMSCRIPTEN})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -s USE_SDL=2 -std=c++14")
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/imgui_interop/wimgui_interop.html DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
    find_package(SDL2 REQUIRED)
    find_package(OpenGL REQUIRED)
endif()

include_directories(imgui_interop/src)
include_directories(SYSTEM imgui_interop/external ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

add_executable( wimgui_interop
    imgui_interop/external/imgui.h
    imgui_interop/external/imgui.cpp
    imgui_interop/external/imgui_demo.cpp
    imgui_interop/external/imgui_draw.cpp
    imgui_interop/src/imgui_impl_sdl.h
    imgui_interop/src/imgui_impl_sdl.cpp
    imgui_interop/src/main.cpp
)

set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++14")

target_link_libraries(wimgui_interop libwULIS3 ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
