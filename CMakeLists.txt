cmake_minimum_required(VERSION 3.28.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Algorithm_Visualizer VERSION 1.0)

include(FetchContent)

#SFML
set(BUILD_SHARED_LIBS OFF)
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/external/SFML)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/SFML/include
)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} algorithm_visualizer.cpp ${SRC_FILES})
# Linkowanie bibliotek SFML
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/SFML/lib)
