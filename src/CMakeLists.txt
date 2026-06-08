add_subdirectory(resource)
add_subdirectory(common)
add_subdirectory(GUI)
add_subdirectory(event)
add_subdirectory(core)

add_executable(alviz main.cpp)

target_sources(alviz PRIVATE FILE_SET CXX_MODULES FILES ${MY_MODULES})

target_link_libraries(alviz PRIVATE GUI_lib core_lib common_lib resource_lib
                                    event_lib)
