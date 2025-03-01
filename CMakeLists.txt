cmake_minimum_required(VERSION 3.28.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Algorithm_Visualizer VERSION 1.0)

include(FetchContent)

# Define SFML directory
set(SFML_DIR ${CMAKE_SOURCE_DIR}/external/SFML)
set(SFML_BUILD_DIR ${SFML_DIR}/build)

# Check if SFML directory exists and is non-empty
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
    # Make sure we are fully disconnected from CMake cache
    set(FETCHCONTENT_FULLY_DISCONNECTED ON)
    set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

    # Ensure SFML is compiled as a static library
    set(BUILD_SHARED_LIBS OFF)

    # Manually fetch SFML before using FetchContent
    execute_process(
        COMMAND git clone --branch 2.5.1 --depth 1 https://github.com/SFML/SFML.git ${SFML_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external
        RESULT_VARIABLE GIT_CLONE_RESULT
    )

    if(NOT GIT_CLONE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone SFML repository!")
    endif()

    # Declare SFML fetch
    FetchContent_Declare(
        SFML
        SOURCE_DIR ${SFML_DIR}  # Ensure SFML is stored in external/SFML
        BINARY_DIR ${SFML_BUILD_DIR}  # Force SFML to build inside external/SFML/build
    )

    # Fetch and build SFML
    FetchContent_MakeAvailable(SFML)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} algorithm_visualizer.cpp ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
