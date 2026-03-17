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
                          uint8_t size, uint32_t style) {
  _text.setString(text);
  _text.setPosition({pos.x, pos.y});
  _text.setFillColor({color.r, color.g, color.b, color.a});
  _text.setCharacterSize(size);
  _text.setStyle(style);
}

void CanvasSFML::_setRectPosAndSize(FloatRect bounds) {
  _rectShape.setPosition({bounds.x, bounds.y});
  _rectShape.setSize({bounds.width, bounds.height});
}
};  // namespace alviz::gui
