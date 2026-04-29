module;

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdint>

export module Alviz.App;

export namespace alviz {
class App {
 public:
  void run();

 private:
  void createScreen();
  void handleEvents();
  void render();

  sf::RenderWindow window_;
  sf::Font font_;

  bool running_;
  uint16_t width_ = 1280;
  uint16_t height_ = 720;
  std::string name_ = "Algorithm Visualizer";
};
}  // namespace alviz
