add_library(event_lib STATIC)

target_sources(
  event_lib
  PRIVATE eventDispatcherImp.cpp eventManagerImp.cpp playerInputImp.cpp
          listenerConnectionImp.cpp
  PUBLIC FILE_SET
         CXX_MODULES
         FILES
         eventDispatcher.cppm
         eventManager.cppm
         playerInput.cppm
         IKeyboardListener.cppm
         IMouseListener.cppm
         IWindowListener.cppm
         listenerConnection.cppm
         events.cppm)

target_link_libraries(event_lib PUBLIC SFML::Graphics SFML::Window SFML::System
                                       common_lib utils_lib)
