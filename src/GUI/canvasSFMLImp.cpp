import GUI.CanvasSFML;

namespace alviz::gui {
void CanvasSFML::drawRect(FloatRect bounds, Color fill) {
  setRectPosAndSize_(bounds);
  rectShape_.setFillColor({fill.r, fill.g, fill.b, fill.a});
}

void CanvasSFML::drawBorder(FloatRect bounds, Color color,
                            math::f32 thickness) {
  setRectPosAndSize_(bounds);
  rectShape_.setOutlineColor({color.r, color.g, color.b, color.a});
  rectShape_.setOutlineThickness(thickness);
}

void CanvasSFML::drawText(const std::string& text, Vec2 pos, Color color,
                          math::u8 size, TextStyle style) {
  text_.setString(text);
  text_.setPosition({pos.x, pos.y});
  text_.setFillColor({color.r, color.g, color.b, color.a});
  text_.setCharacterSize(size);
  text_.setStyle(toSFML(style));
}

void CanvasSFML::setRectPosAndSize_(FloatRect bounds) {
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
};  // namespace alviz::gui
