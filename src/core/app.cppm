module;

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

export module Alviz.App;

import GUI.Container;
import Alviz.Math;
import Alviz.Events;
import Alviz.EventManager;

export namespace alviz {
class App : public IWindowListener, public EventManager {
 public:
  void run();
  void handleEvents();
  void createScreen();
  void loadResources();
  void render();

  void onWindowClosed() override;
  void onWindowResized(FloatRect size) override;

 private:
  EventManager eventManger_;
  sf::RenderWindow window_;
  gui::Container mainContainer_;
  sf::Font font_;

  bool running_;
  math::u16 width_ = 1280;
  math::u16 height_ = 720;
  std::string name_ = "Algorithm Visualizer";
};
}  // namespace alviz
