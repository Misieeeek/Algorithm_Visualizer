#ifndef ALGOVIZ_GUI_TEXTWIDGET_H_
#define ALGOVIZ_GUI_TEXTWIDGET_H_
#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"
#include "Widget.h"

namespace alviz::gui {
class TextWidget : public Widget {
 public:
  void render(ICanvas& canvas) override;

 private:
};
}  // namespace alviz::gui

#endif  // ALGOVIZ_GUI_TEXTWIDGET_H_
