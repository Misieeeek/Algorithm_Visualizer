#ifndef ALGOVIZ_APP_H_
#define ALGOVIZ_APP_H_
#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

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

#endif  //ALGOVIZ_APP_H_
