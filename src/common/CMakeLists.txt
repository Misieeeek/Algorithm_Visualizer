add_library(common_lib STATIC)

target_link_libraries(common_lib PUBLIC SFML::Graphics SFML::Window
                                        SFML::System)

target_sources(common_lib PUBLIC FILE_SET CXX_MODULES FILES math.cppm)
