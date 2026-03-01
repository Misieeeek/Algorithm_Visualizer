#ifndef INAVIGABLE_H
#define INAVIGABLE_H

#include "SFML/System/Vector2.hpp"
#include "SFML/Window.hpp"
#pragma once

class IInteractable {
 public:
  virtual ~IInteractable() = default;

  virtual void handle_key_press(sf::Keyboard::Key key) = 0;
  virtual void handle_text_input(const sf::Event::TextEvent& text) = 0;
  virtual void habdle_mouse_click(const sf::Vector2i& position) = 0;
};

#endif
