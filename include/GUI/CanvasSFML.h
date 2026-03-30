#ifndef ALGOVIZ_GUI_CANVAS_SFML_H_
#define ALGOVIZ_GUI_CANVAS_SFML_H_
#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "ICanvas.h"

namespace alviz::gui {
class CanvasSFML : public ICanvas {
  using TextStyle = styles::TextStyle;

 public:
  void drawRect(FloatRect bounds, Color fill) override;
  void drawBorder(FloatRect bounds, Color color,
                  float thickness = 1.0) override;
  void drawText(const std::string& text, Vec2 pos, Color color,
                uint8_t size = 14,
                TextStyle style = TextStyle::Regular) override;

 private:
  void _setRectPosAndSize(FloatRect bounds);
  static sf::Text::Style toSFML(TextStyle style);
  sf::RectangleShape _rectShape;
  sf::Text _text;
};
};  // namespace alviz::gui
#endif
