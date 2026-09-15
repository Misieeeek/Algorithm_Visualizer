add_executable(GUI_test)

target_sources(
  GUI_test
  PRIVATE FILE_SET
          CXX_MODULES
          FILES
          testButton.cppm
          testCanvasSFML.cppm
          testContainer.cppm
          testGUIRoot.cppm
          testInput.cppm
          testLabel.cppm
          testWidget.cppm)

target_link_libraries(GUI_test PRIVATE GUI_lib event_lib GTest::gtest_main
                                       SFML::Graphics SFML::Window SFML::System)

gtest_discover_tests(GUI_test)
