add_library(core_lib STATIC)

target_sources(
  core_lib
  PRIVATE appImp.cpp stateManagerImp.cpp stateImp.cpp
  PUBLIC FILE_SET CXX_MODULES FILES app.cppm stateManager.cppm state.cppm)

target_link_libraries(core_lib PUBLIC SFML::Graphics SFML::Window SFML::System
                                      common_lib GUI_lib resource_lib)
