module;

#include <string>

export module GUI.ICanvas;

import Alviz.Math;
import GUI.Common;
import GUI.Styles;

export namespace alviz::gui {
namespace math = alviz::math;

class ICanvas {
 public:
  using TextStyle = styles::TextStyle;

  virtual ~ICanvas() = default;

  virtual void drawRect(FloatRect bounds, Color fill) = 0;
  virtual void drawBorder(FloatRect bounds, Color color,
                          math::f32 thickness = 1.0) = 0;
  virtual void drawText(const std::string& text, Vec2 pos, Color color,
                        math::u8 size = 14,
                        TextStyle style = TextStyle::Regular) = 0;
};
}  // namespace alviz::gui
