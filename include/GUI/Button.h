#ifndef ALGOVIZ_GUI_BUTTON_H_
#define ALGOVIZ_GUI_BUTTON_H_
#pragma once

#include <functional>

#include "GUI/ICanvas.h"
#include "GUI/Label.h"
#include "GUI/TextWidget.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"

namespace alviz::gui {
class Button : public TextWidget {
 public:
  void render(ICanvas& canvas) override;
  void setOnPress(std::function<void()> callback);
  void onMouseClick(float xPos, float yPos) override;
  void onKey(Key key) override;
  void press();

 private:
  std::function<void()> _onClick;
  styles::ButtonStyle _style;
  std::string _text;
};
}  // namespace alviz::gui

#endif  // ALGOVIZ_GUI_BUTTON_H_
