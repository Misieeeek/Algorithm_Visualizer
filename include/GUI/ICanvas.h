#ifndef ALGOVIZ_GUI_ICANVAS_H_
#define ALGOVIZ_GUI_ICANVAS_H_
#pragma once

#include <string>

#include "AlvizMath.h"
#include "GUI/Common.h"
#include "GUI/Styles.h"

namespace alviz::gui {
class ICanvas {
  using TextStyle = styles::TextStyle;

 public:
  virtual ~ICanvas() = default;

  virtual void drawRect(FloatRect bounds, Color fill) = 0;
  virtual void drawBorder(FloatRect bounds, Color color,
                          float thickness = 1.0) = 0;
  virtual void drawText(const std::string& text, Vec2 pos, Color color,
                        uint8_t size = 14,
                        TextStyle style = TextStyle::Regular) = 0;
};
}  // namespace alviz::gui
#endif
