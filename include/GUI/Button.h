#ifndef ALGOVIZ_GUI_BUTTON_H_
#define ALGOVIZ_GUI_BUTTON_H_
#pragma once

#include "GUI/ICanvas.h"
#include "GUI/Label.h"
#include "GUI/TextWidget.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"

namespace alviz::gui {
class Button : public TextWidget {
 public:
  void render(ICanvas& canvas) override;
  void press();

 private:
  styles::ButtonStyle _style;
  std::string _text;
};
}  // namespace alviz::gui

#endif  // ALGOVIZ_GUI_BUTTON_H_
