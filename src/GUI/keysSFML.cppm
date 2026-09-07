module;

#include <SFML/Window/Keyboard.hpp>

export module GUI.Key;

import Alviz.Math;

export namespace alviz::gui {
enum class Key : alviz::math::u8 {
  Unknown = 0,
  Enter,
  Escape,
  Backspace,
  Delete,
  Tab,
  Left,
  Right,
  Up,
  Down,
  Home,
  End,
  PageUp,
  PageDown,
  Space,
};

Key translateKey(sf::Keyboard::Key code) {
  switch (code) {
    case sf::Keyboard::Key::Enter:
      return Key::Enter;
    case sf::Keyboard::Key::Escape:
      return Key::Escape;
    case sf::Keyboard::Key::Backspace:
      return Key::Backspace;
    case sf::Keyboard::Key::Delete:
      return Key::Delete;
    case sf::Keyboard::Key::Tab:
      return Key::Tab;
    case sf::Keyboard::Key::Left:
      return Key::Left;
    case sf::Keyboard::Key::Right:
      return Key::Right;
    case sf::Keyboard::Key::Up:
      return Key::Up;
    case sf::Keyboard::Key::Down:
      return Key::Down;
    case sf::Keyboard::Key::Home:
      return Key::Home;
    case sf::Keyboard::Key::End:
      return Key::End;
    case sf::Keyboard::Key::PageUp:
      return Key::PageUp;
    case sf::Keyboard::Key::PageDown:
      return Key::PageDown;
    case sf::Keyboard::Key::Space:
      return Key::Space;
    default:
      return Key::Unknown;
  }
}
}  // namespace alviz::gui
