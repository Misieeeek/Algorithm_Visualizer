cmake_minimum_required(VERSION 3.28.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Algorithm_Visualizer VERSION 1.0)

find_package(SFML 2.6.1 REQUIRED COMPONENTS graphics window system)
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/external/SFML")
set(CMAKE_PREFIX_PATH ${SFML_ROOT})
include_directories(${SFML_INCLUDE_DIRS})

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} algorithm_visualizer.cpp ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
