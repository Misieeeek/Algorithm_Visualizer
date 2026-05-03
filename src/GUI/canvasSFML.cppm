module;

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

export module GUI.CanvasSFML;

import GUI.Common;
import GUI.Styles;
import Alviz.Math;
import GUI.ICanvas;

export namespace alviz::gui {
class CanvasSFML : public ICanvas {
 public:
  using TextStyle = styles::TextStyle;

  void drawRect(FloatRect bounds, Color fill) override;
  void drawBorder(FloatRect bounds, Color color,
                  math::f32 thickness = 1.0) override;
  void drawText(const std::string& text, Vec2 pos, Color color,
                math::u8 size = 14,
                TextStyle style = TextStyle::Regular) override;

 private:
  void setRectPosAndSize_(FloatRect bounds);
  static math::u32 toSFML(TextStyle style);
  static sf::Color toSFML(Color color);
  sf::RectangleShape rectShape_;
  sf::Text text_;
};
};  // namespace alviz::gui
