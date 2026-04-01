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

uint32_t CanvasSFML::toSFML(TextStyle style) {
  uint32_t result = sf::Text::Regular;

  if (style & TextStyle::Bold) {
    result |= sf::Text::Bold;
  }
  if (style & TextStyle::Italic) {
    result |= sf::Text::Italic;
  }
  if (style & TextStyle::Underline) {
    result |= sf::Text::Underlined;
  }

  return result;
}

sf::Color CanvasSFML::toSFML(Color color) {
  return sf::Color(color.r, color.g, color.b, color.a);
}
};  // namespace alviz::gui
