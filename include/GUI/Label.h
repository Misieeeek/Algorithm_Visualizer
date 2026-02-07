#ifndef ALGOVIZ_GUI_LABEL_H_
#define ALGOVIZ_GUI_LABEL_H_
#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"
#include "TextWidget.h"

namespace GUI {
class Label : public TextWidget {
 public:
  virtual void draw(sf::RenderWindow*);

 private:
};
}  // namespace GUI

#endif  //ALGOVIZ_GUI_LABEL_H_
