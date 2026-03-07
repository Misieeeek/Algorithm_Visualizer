#ifndef ALGOVIZ_CORE_APPLICATION_H_
#define ALGOVIZ_CORE_APPLICATION_H_
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

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
};
}  // namespace alviz

#endif  // ALGOVIZ_CORE_APPLICATION_H_
