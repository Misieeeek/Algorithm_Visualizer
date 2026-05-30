module;

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

module GUI.CanvasSFML;

import Alviz.Math;
import GUI.Common;
import GUI.Styles;

namespace alviz::gui {

CanvasSFML::CanvasSFML(sf::RenderWindow& window, const sf::Font& defaultFont)
    : window_(window), text_(defaultFont) {}

void CanvasSFML::drawRect(FloatRect bounds, Color fill) {
  setRectPosAndSize(bounds);
  rectShape_.setFillColor(toSFML(fill));
  window_.draw(rectShape_);
}

void CanvasSFML::drawBorder(FloatRect bounds, Color color,
                            math::f32 thickness) {
  setRectPosAndSize(bounds);
  rectShape_.setOutlineColor(toSFML(color));
  rectShape_.setOutlineThickness(thickness);
  window_.draw(rectShape_);
}

void CanvasSFML::drawText(const std::string& text, Vec2 pos, Color color,
                          math::u8 size, TextStyle style) {
  text_.setString(text);
  text_.setPosition({pos.x, pos.y});
  text_.setFillColor(toSFML(color));
  text_.setCharacterSize(size);
  text_.setStyle(toSFML(style));
  window_.draw(text_);
}

void CanvasSFML::setRectPosAndSize(FloatRect bounds) {
  rectShape_.setPosition({bounds.x, bounds.y});
  rectShape_.setSize({bounds.width, bounds.height});
}

math::u32 CanvasSFML::toSFML(TextStyle style) {
  math::u32 result = sf::Text::Regular;

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

void CanvasSFML::drawCursor(FloatRect bounds, const std::string& textBefore) {
  sf::Text temp = text_;
  temp.setString(textBefore);
  float cursorX = bounds.x + 4 + temp.getLocalBounds().size.x;

  sf::RectangleShape cursor;
  cursor.setPosition({cursorX, bounds.y + 4});
  cursor.setSize({2.F, bounds.height - 8});
  cursor.setFillColor(sf::Color::White);
  window_.draw(cursor);
}
};  // namespace alviz::gui
