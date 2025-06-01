cmake_minimum_required(VERSION 3.28.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Algorithm_Visualizer VERSION 1.0)

include(FetchContent)

set(SFML_DIR ${CMAKE_SOURCE_DIR}/external/SFML)
set(SFML_BUILD_DIR ${SFML_DIR}/build)

if(NOT EXISTS ${CMAKE_BINARY_DIR})
    message(STATUS "Build directory doesn't exist. Creating it...")
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

if(NOT EXISTS ${SFML_BUILD_DIR})
    message(STATUS "SFML build directory doesn't exist. Creating it...")
    file(MAKE_DIRECTORY ${SFML_BUILD_DIR})
endif()

if(NOT EXISTS ${SFML_DIR})
    message(STATUS "Directory 'external/SFML' doesn't exist. Creating it...")
    file(MAKE_DIRECTORY ${SFML_DIR})
    set(FETCH_SFML TRUE)
elseif(IS_DIRECTORY ${SFML_DIR})
    file(GLOB SFML_CONTENTS ${SFML_DIR}/*)
    list(LENGTH SFML_CONTENTS CONTENT_COUNT)
    if(CONTENT_COUNT EQUAL 0)
        message(STATUS "Directory 'external/SFML' is empty. Installing SFML...")
        set(FETCH_SFML TRUE)
    else()
        message(STATUS "SFML directory exists with content. Using it.")
        set(FETCH_SFML FALSE)
    endif()
endif()

if(FETCH_SFML)
    set(FETCHCONTENT_FULLY_DISCONNECTED_BACKUP ${FETCHCONTENT_FULLY_DISCONNECTED})
    set(FETCHCONTENT_FULLY_DISCONNECTED OFF)
    set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
    set(BUILD_SHARED_LIBS OFF)
    
    execute_process(
        COMMAND git clone --branch 2.5.1 --depth 1 https://github.com/SFML/SFML.git ${SFML_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external
        RESULT_VARIABLE GIT_CLONE_RESULT
    )
    
    if(NOT GIT_CLONE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone SFML repository!")
    endif()
    
    FetchContent_Declare(
        SFML
        SOURCE_DIR ${SFML_DIR}  
        BINARY_DIR ${SFML_BUILD_DIR}  
    )
    FetchContent_MakeAvailable(SFML)
    
    if(DEFINED FETCHCONTENT_FULLY_DISCONNECTED_BACKUP)
        set(FETCHCONTENT_FULLY_DISCONNECTED ${FETCHCONTENT_FULLY_DISCONNECTED_BACKUP})
    endif()
endif()

set(FETCHCONTENT_FULLY_DISCONNECTED OFF)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1  
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} algorithm_visualizer.cpp ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

enable_testing()

if(TARGET gtest_main)
    add_executable(tests
        tests/insertion_sort_algos.cpp
        ${SRC_FILES}
    )
    
    target_include_directories(tests
        PRIVATE
            ${CMAKE_SOURCE_DIR}/include
    )
    
    target_link_libraries(tests
        PRIVATE
            GTest::gtest_main
            sfml-graphics
            sfml-window
            sfml-system
    )
    
    include(GoogleTest)
    gtest_discover_tests(tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    
    message(STATUS "Tests configured successfully")
else()
    message(WARNING "GoogleTest not available - skipping test build")
endif()
