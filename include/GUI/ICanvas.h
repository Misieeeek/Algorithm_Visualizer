#ifndef ALGOVIZ_GUI_ICANVAS_H_
#define ALGOVIZ_GUI_ICANVAS_H_
#pragma once

#include <string>

#include "AlvizMath.h"
#include "GUI/Common.h"

namespace alviz::gui {
class ICanvas {
 public:
  virtual ~ICanvas() = default;

  virtual void drawRect(FloatRect bounds, Color fill) = 0;
  virtual void drawBorder(FloatRect bounds, Color color,
                          float thickness = 1.0) = 0;
  virtual void drawText(const std::string& text, Vec2 pos, Color color,
                        uint8_t size = 14, uint32_t style = 0) = 0;
};
}  // namespace alviz::gui
#endif
