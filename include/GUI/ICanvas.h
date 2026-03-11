#ifndef ALGOVIZ_GUI_ICANVAS_H_
#define ALGOVIZ_GUI_ICANVAS_H_
#pragma once

namespace GUI {
class ICanvas {
 public:
  virtual ~ICanvas() = 0;
  virtual void drawRect() = 0;
  virtual void drawBorder() = 0;
  virtual void drawText() = 0;
};
}  // namespace GUI
#endif
