file( GLOB_RECURSE wSDL_Display_source_list RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "SDL_Display.cpp" )
add_executable( wSDL_Display ${wSDL_Display_source_list} )
target_link_libraries( wSDL_Display libwULIS3 )
