module;

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

export module Alviz.App;

import GUI.Container;
import Alviz.Math;

export namespace alviz {
class App {
 public:
  void run();

 private:
  void createScreen();
  void handleEvents();
  void render();
  void loadResources();

  sf::RenderWindow window_;
  sf::Font font_;

  bool running_;
  math::u16 width_ = 1280;
  math::u16 height_ = 720;
  std::string name_ = "Algorithm Visualizer";

  gui::Container mainContainer_;
};
}  // namespace alviz
