#include "GUI/CanvasSFML.h"

namespace alviz::gui {
void CanvasSFML::drawRect(FloatRect bounds, Color fill) {
  _setRectPosAndSize(bounds);
  _rectShape.setFillColor({fill.r, fill.g, fill.b, fill.a});
}

void CanvasSFML::drawBorder(FloatRect bounds, Color color, float thickness) {
  _setRectPosAndSize(bounds);
  _rectShape.setOutlineColor({color.r, color.g, color.b, color.a});
  _rectShape.setOutlineThickness(thickness);
}

void CanvasSFML::drawText(const std::string& text, Vec2 pos, Color color,
                          uint8_t size, TextStyle style) {
  _text.setString(text);
  _text.setPosition({pos.x, pos.y});
  _text.setFillColor({color.r, color.g, color.b, color.a});
  _text.setCharacterSize(size);
  _text.setStyle(toSFML(style));
}

void CanvasSFML::_setRectPosAndSize(FloatRect bounds) {
  _rectShape.setPosition({bounds.x, bounds.y});
  _rectShape.setSize({bounds.width, bounds.height});
}

sf::Text::Style CanvasSFML::toSFML(TextStyle style) {
  switch (style) {
    case TextStyle::Bold:
      return sf::Text::Bold;
    case TextStyle::Italic:
      return sf::Text::Italic;
    case TextStyle::Underline:
      return sf::Text::Underlined;
    default:
      return sf::Text::Regular;
  }
}
};  // namespace alviz::gui
