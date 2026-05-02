find_package(GTest REQUIRED)

enable_testing()
include(GoogleTest)
include(${CMAKE_SOURCE_DIR}/cmake/Coverage.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Valgrind.cmake)

add_executable(unit_tests
    insertion_sort_algos_test.cpp 
)

target_link_libraries(unit_tests PRIVATE
    GTest::gtest_main GTest::gmock
    core_lib
)

option(USE_VALGRIND "Prepare binary for Valgrind (disables Sanitizers)" OFF)

if(ENABLE_COVERAGE)
    message(STATUS "Coverage is ON - Disabling ThreadSanitizer")
elseif(USE_VALGRIND)
    message(STATUS "Valgrind mode ON - Disabling ThreadSanitizer to avoid conflicts")
    target_compile_options(unit_tests PRIVATE -g)
else()
    message(STATUS "Standard Debug - Enabling ThreadSanitizer")
    target_compile_options(unit_tests PRIVATE -fsanitize=thread -g -O1)
    target_link_options(unit_tests PRIVATE -fsanitize=thread)
endif()

gtest_discover_tests(unit_tests EXTRA_ARGS "--gtest_brief=1")

TestCoverage(unit_tests)
Memcheck(unit_tests)
