cmake_minimum_required( VERSION 3.13.2 )

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
        "samples/SimpleFluid/main.cpp"
        "samples/SimpleFluid/SimpleFluid.cpp"
        "samples/SimpleFluid/SimpleFluid.h"
    )

    add_executable( SimpleFluid ${source_list} )
    set_target_properties( SimpleFluid PROPERTIES CMAKE_AUTOMOC ON )
    target_link_libraries(
        SimpleFluid
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