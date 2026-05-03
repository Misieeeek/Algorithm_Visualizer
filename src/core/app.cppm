module;

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

export module Alviz.App;

import std;
import Alviz.Math;

export namespace alviz {
class App {
 public:
  void run();

 private:
  void createScreen_();
  void handleEvents_();
  void render_();

  sf::RenderWindow window_;
  sf::Font font_;

  bool running_;
  math::u16 width_ = 1280;
  math::u16 height_ = 720;
  std::string name_ = "Algorithm Visualizer";
};
}  // namespace alviz
