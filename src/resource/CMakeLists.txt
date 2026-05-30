add_library(resource_lib STATIC)

target_sources(
  resource_lib
  PRIVATE resourceManagerImp.cpp
  PUBLIC FILE_SET CXX_MODULES FILES resourceManager.cppm)

target_link_libraries(resource_lib PUBLIC SFML::Graphics SFML::Window
                                          SFML::System)
