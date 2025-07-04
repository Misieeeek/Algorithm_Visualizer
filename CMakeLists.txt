cmake_minimum_required(VERSION 3.28.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Algorithm_Visualizer VERSION 1.0)

include(FetchContent)

set(FETCHCONTENT_QUIET ON)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)

# SET SFML OPTIONS BEFORE MAKING IT AVAILABLE
set(SFML_BUILD_AUDIO ON CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# MAKE SFML AVAILABLE
FetchContent_MakeAvailable(SFML)

# FETCH GOOGLETEST
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ENABLE COMPILE COMMANDS EXPORT
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# COLLECT SOURCE FILES
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# CREATE MAIN EXECUTABLE
add_executable(${PROJECT_NAME} algorithm_visualizer.cpp ${SRC_FILES})

# SET INCLUDE DIRECTORIES
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
)

# LINK LIBRARIES
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

# PLATFORM-SPECIFIC LINKING
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-main)
endif()

# ENABLE TESTING
enable_testing()

# CREATE TESTS EXECUTABLE IF GOOGLETEST IS AVAILABLE
if(TARGET gtest_main)
    # INSERTION SORT TESTS
    add_executable(insertion_sort_tests
        tests/insertion_sort_algos_tests.cpp
        ${SRC_FILES}
    )
    
    target_include_directories(insertion_sort_tests
        PRIVATE
            ${CMAKE_SOURCE_DIR}/include
    )
    
    target_link_libraries(insertion_sort_tests
        PRIVATE
            GTest::gtest_main
            sfml-graphics
            sfml-window
            sfml-system
    )
    
    # SELECTION SORT TESTS
    add_executable(selection_sort_tests
        tests/selection_sort_algos_tests.cpp
        ${SRC_FILES}
    )
    
    target_include_directories(selection_sort_tests
        PRIVATE
            ${CMAKE_SOURCE_DIR}/include
    )
    
    target_link_libraries(selection_sort_tests
        PRIVATE
            GTest::gtest_main
            sfml-graphics
            sfml-window
            sfml-system
    ) 
    # MERGE SORT TESTS
    add_executable(merge_sort_tests
        tests/merge_sort_algos_tests.cpp
        ${SRC_FILES}
    )
    
    target_include_directories(merge_sort_tests
        PRIVATE
            ${CMAKE_SOURCE_DIR}/include
    )
    
    target_link_libraries(merge_sort_tests
        PRIVATE
            GTest::gtest_main
            sfml-graphics
            sfml-window
            sfml-system
    )
    # PLATFORM-SPECIFIC LINKING FOR TESTS
    if(WIN32)
        target_link_libraries(insertion_sort_tests PRIVATE sfml-main)
        target_link_libraries(selection_sort_tests PRIVATE sfml-main)
    endif()
    
    include(GoogleTest)
    gtest_discover_tests(insertion_sort_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        TEST_PREFIX "InsertionSort."
    )
    
    gtest_discover_tests(selection_sort_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        TEST_PREFIX "SelectionSort."
    )    
    message(STATUS "Tests configured successfully")
else()
    message(WARNING "GoogleTest not available - skipping test build")
endif()
