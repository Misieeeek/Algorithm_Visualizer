add_library(event_lib STATIC)

target_sources(
  event_lib
  PRIVATE eventDispatcherImp.cpp eventHandlerImp.cpp playerInputImp.cpp
  PUBLIC FILE_SET
         CXX_MODULES
         FILES
         IKeyboardListener.cppm
         IMouseListener.cppm
         IWindowListener.cppm
         eventDispatcher.cppm
         eventHandler.cppm
         playerInput.cppm)

target_link_libraries(event_lib PUBLIC SFML::Graphics SFML::Window SFML::System)
