file( GLOB_RECURSE wFormats_source_list RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Formats.cpp" )
add_executable( wFormats ${wFormats_source_list} )
target_link_libraries( wFormats libwULIS3 )
