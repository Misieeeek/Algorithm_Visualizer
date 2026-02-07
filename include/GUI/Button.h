#ifndef ALGOVIZ_GUI_BUTTON_H_
#define ALGOVIZ_GUI_BUTTON_H_
#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"
#include "TextWidget.h"

namespace GUI {
class Button : public TextWidget {
 public:
  void draw(sf::RenderWindow*) override;
  void press();

 private:
};
}  // namespace GUI

#endif  // ALGOVIZ_GUI_BUTTON_H_
