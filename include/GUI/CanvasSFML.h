#ifndef ALGOVIZ_GUI_CANVAS_SFML_H_
#define ALGOVIZ_GUI_CANVAS_SFML_H_
#pragma once

#include "ICanvas.h"

namespace alviz::gui {
class CanvasSFML : public ICanvas {
 public:
  void drawRect(FloatRect bounds, Color fill) override;
  void drawBorder(FloatRect bounds, Color color,
                  float thickness = 1.0) override;
  void drawText(const std::string& text, Vec2 pos, Color color,
                uint8_t size = 14) override;
};
};  // namespace alviz::gui
#endif
