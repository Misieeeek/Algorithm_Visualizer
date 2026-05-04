add_library(GUI_lib STATIC)

target_sources(
  GUI_lib
  PRIVATE buttonImp.cpp canvasSFMLImp.cpp containerImp.cpp widgetImp.cpp
          textWidgetImp.cpp
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
         textWidget.cppm
         widget.cppm)

target_link_libraries(GUI_lib PUBLIC SFML::Graphics SFML::Window SFML::System
                                     common_lib)
