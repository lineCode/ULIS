
# Function to register a target for clang-tidy
function(perform_clang_tidy check_target target)
    set(includes "$<TARGET_PROPERTY:${target},INCLUDE_DIRECTORIES>")

    add_custom_target(
        ${check_target}
        COMMAND
            ${clang_tidy_EXECUTABLE}
                -p\t${PROJECT_BINARY_DIR}
                ${ARGN}
                -checks=*
                "$<$<NOT:$<BOOL:${CMAKE_EXPORT_COMPILE_COMMANDS}>>:--\t$<$<BOOL:${includes}>:-I$<JOIN:${includes},\t-I>>>"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
    add_dependencies(${check_target} ${target})
endfunction()
