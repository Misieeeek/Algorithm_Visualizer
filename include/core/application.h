#ifndef ALGOVIZ_CORE_APPLICATION_H_
#define ALGOVIZ_CORE_APPLICATION_H_
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdint>

namespace alviz {
class Application {
 public:
  virtual ~Application() = default;
  void run();

 private:
  void handleEvents();
  void render();

  sf::RenderWindow _window;
  bool _running;
  uint16_t _width = 1280;
  uint16_t _height = 720;
  std::string _name = "Algorithm Visualizer";
};
}  // namespace alviz

#endif  // ALGOVIZ_CORE_APPLICATION_H_
