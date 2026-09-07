add_library(GUI_lib STATIC)

target_sources(
  GUI_lib
  PRIVATE buttonImp.cpp
          canvasSFMLImp.cpp
          containerImp.cpp
          widgetImp.cpp
          inputImp.cpp
          labelImp.cpp
          GUIRootImp.cpp
  PUBLIC FILE_SET
         CXX_MODULES
         FILES
         ICanvas.cppm
         button.cppm
         canvasSFML.cppm
         common.cppm
         label.cppm
         container.cppm
         styles.cppm
         input.cppm
         widget.cppm
         GUIRoot.cppm)

target_link_libraries(GUI_lib PUBLIC SFML::Graphics SFML::Window SFML::System
                                     common_lib event_lib)
