#ifndef ALGOVIZ_GUI_TEXTWIDGET_H_
#define ALGOVIZ_GUI_TEXTWIDGET_H_
#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"
#include "Widget.h"

namespace GUI {
class TextWidget : public Widget {
 public:
  virtual void draw(sf::RenderWindow*);

 private:
};
}  // namespace GUI

#endif  //ALGOVIZ_GUI_TEXTWIDGET_H_
