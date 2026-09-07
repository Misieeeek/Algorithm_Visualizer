module;

#include <SFML/Window/Event.hpp>

export module Alviz.Events:MouseListener;

import Alviz.Math;

export namespace alviz {
class IMouseListener {
 public:
  virtual ~IMouseListener() = default;

  virtual void onMouseMove(const sf::Event::MouseMoved& evnt) {}
  virtual void onButtonPressed(const sf::Event::MouseButtonPressed& evnt) {}
};
}  // namespace alviz
