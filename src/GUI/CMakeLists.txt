add_library(GUI_lib STATIC)

target_sources(GUI_lib
    PRIVATE
    PUBLIC
        FILE_SET CXX_MODULES FILES
)

target_link_libraries(GUI_lib PUBLIC SFML::Graphics)

