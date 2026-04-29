function(Memcheck target)
    if(NOT UNIX OR APPLE)
        message(STATUS "Skipping Valgrind")
        return()
    endif()
    find_program(VALGRIND_PATH valgrind)
    if (NOT VALGRIND_PATH)
        message(WARNING "Valgrind not found, skipping analysis for ${target}")
        return()
    endif()
    add_custom_target(memcheck_${target}
        COMMAND ${VALGRIND_PATH} --leak-check=full --show-leak-kinds=all
                #--track-origins=yes
                --error-exitcode=1
                $<TARGET_FILE:${target}>
        DEPENDS ${target}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endfunction()


