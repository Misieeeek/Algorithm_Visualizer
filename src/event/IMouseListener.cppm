module;

#include <SFML/Window/Event.hpp>

export module Alviz.Events:MouseListener;

import Alviz.Math;

export namespace alviz {
class IMouseListener {
 public:
  virtual ~IMouseListener() = default;

  virtual void onMouseMove(Vec2 pos) {};
  virtual void onMouseClick(Vec2 pos) {};
  virtual void onButtonPressed(const sf::Event::MouseButtonPressed& evnt) {}
};
}  // namespace alviz
