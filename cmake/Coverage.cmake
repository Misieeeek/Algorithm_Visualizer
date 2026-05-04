option(ENABLE_COVERAGE "Enable code coverage analysis" OFF)

function(TestCoverage target)
  if(NOT ENABLE_COVERAGE)
    message(
      STATUS
        "Coverage is DISABLED for ${target}. Use -DENABLE_COVERAGE=ON to enable."
    )
    return()
  endif()

  if(NOT UNIX OR APPLE)
    message(STATUS "Skipping LCOV")
    return()
  endif()

  find_program(LCOV_PATH lcov)
  find_program(GENHTML_PATH genhtml)

  if(NOT LCOV_PATH OR NOT GENHTML_PATH)
    message(
      WARNING
        "LCOV_PATH and/or GENHTML_PATH not found, skipping coverage_${target}")
    return()
  endif()

  target_compile_options(${target} PRIVATE --coverage -g -O0)
  target_link_options(${target} PRIVATE --coverage)

  add_custom_target(
    coverage_${target}
    COMMENT "${target} test coverage"
    COMMAND ${LCOV_PATH} -d . --zerocounters
    COMMAND $<TARGET_FILE:${target}>
    COMMAND ${LCOV_PATH} -d . --capture --ignore-errors inconsistent -o
            coverage.info
    COMMAND ${LCOV_PATH} -r coverage.info '/usr/include/*' '*/c++/*' '*conan'
            --ignore-errors inconsistent --ignore-errors unused -o filtered.info
    COMMAND ${GENHTML_PATH} -o html_coverage_${target} filtered.info --legend
            --ignore-errors inconsistent
    COMMAND ${CMAKE_COMMAND} -E rm -f coverage.info filtered.info
    DEPENDS ${target}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()
