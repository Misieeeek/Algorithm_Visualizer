cmake_minimum_required(VERSION 3.31.5)
project(Algorithm_Visualizer VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML CONFIG REQUIRED)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(Algorithm_visualizer
  algorithm_visualizer.cpp
  ${SRC_FILES}
)

target_link_libraries(Algorithm_visualizer
    PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        sfml-network
)

# SET INCLUDE DIRECTORIES
target_include_directories(Algorithm_visualizer 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
)
# # CREATE MAIN EXECUTABLE
# add_executable(${PROJECT_NAME} algorithm_visualizer.cpp ${SRC_FILES})
#
#
# # LINK LIBRARIES
# target_link_libraries(${PROJECT_NAME} 
#     PRIVATE
#         sfml-graphics
#         sfml-window
#         sfml-system
# )
#
# # PLATFORM-SPECIFIC LINKING
# if(WIN32)
#     target_link_libraries(${PROJECT_NAME} PRIVATE sfml-main)
# endif()
#
# # ENABLE TESTING
# enable_testing()
#
# # CREATE TESTS EXECUTABLE IF GOOGLETEST IS AVAILABLE
# if(TARGET gtest_main)
#     # INSERTION SORT TESTS
#     add_executable(insertion_sort_tests
#         tests/insertion_sort_algos_tests.cpp
#         ${SRC_FILES}
#     )
#     
#     target_include_directories(insertion_sort_tests
#         PRIVATE
#             ${CMAKE_SOURCE_DIR}/include
#     )
#     
#     target_link_libraries(insertion_sort_tests
#         PRIVATE
#             GTest::gtest_main
#             sfml-graphics
#             sfml-window
#             sfml-system
#     )
#     
#     # SELECTION SORT TESTS
#     add_executable(selection_sort_tests
#         tests/selection_sort_algos_tests.cpp
#         ${SRC_FILES}
#     )
#     
#     target_include_directories(selection_sort_tests
#         PRIVATE
#             ${CMAKE_SOURCE_DIR}/include
#     )
#     
#     target_link_libraries(selection_sort_tests
#         PRIVATE
#             GTest::gtest_main
#             sfml-graphics
#             sfml-window
#             sfml-system
#     ) 
#     # MERGE SORT TESTS
#     add_executable(merge_sort_tests
#         tests/merge_sort_algos_tests.cpp
#         ${SRC_FILES}
#     )
#     
#     target_include_directories(merge_sort_tests
#         PRIVATE
#             ${CMAKE_SOURCE_DIR}/include
#     )
#     
#     target_link_libraries(merge_sort_tests
#         PRIVATE
#             GTest::gtest_main
#             sfml-graphics
#             sfml-window
#             sfml-system
#     )
#     
#     # EXCHANGE SORT TESTS
#     add_executable(exchange_sort_tests
#         tests/exchange_sort_algos_tests.cpp
#         ${SRC_FILES}
#     )
#     
#     target_include_directories(exchange_sort_tests
#         PRIVATE
#             ${CMAKE_SOURCE_DIR}/include
#     )
#     
#     target_link_libraries(exchange_sort_tests
#         PRIVATE
#             GTest::gtest_main
#             sfml-graphics
#             sfml-window
#             sfml-system
#     )
#
#     # PLATFORM-SPECIFIC LINKING FOR TESTS
#     if(WIN32)
#         target_link_libraries(insertion_sort_tests PRIVATE sfml-main)
#         target_link_libraries(selection_sort_tests PRIVATE sfml-main)
#     endif()
#     
#     include(GoogleTest)
#     gtest_discover_tests(insertion_sort_tests
#         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#         TEST_PREFIX "InsertionSort."
#     )
#     
#     gtest_discover_tests(selection_sort_tests
#         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#         TEST_PREFIX "SelectionSort."
#     )    
#     message(STATUS "Tests configured successfully")
# else()
#     message(WARNING "GoogleTest not available - skipping test build")
# endif()
