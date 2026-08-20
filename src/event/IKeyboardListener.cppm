module;

#include <SFML/Window/Event.hpp>

export module Alviz.Events:KeyboardListener;

export namespace alviz {
class IKeyboardListener {
 public:
  virtual ~IKeyboardListener() = default;
  virtual void onKeyPressed(const sf::Event::KeyPressed& evnt) {};
};
}  // namespace alviz
