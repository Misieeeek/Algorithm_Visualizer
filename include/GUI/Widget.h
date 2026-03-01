#ifndef ALGOVIZ_GUI_WIDGETFACTORY_H_
#define ALGOVIZ_GUI_WIDGETFACTORY_H_
#pragma once

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Window.hpp"

namespace GUI {
class Widget {
 public:
 private:
  sf::Font _font;
  sf::Text _textDisplay;
  std::string _text;
};
}  // namespace GUI

#endif  // ALGOVIZ_GUI_WIDGETFACTORY_H_
