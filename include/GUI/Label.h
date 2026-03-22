#ifndef ALGOVIZ_GUI_LABEL_H_
#define ALGOVIZ_GUI_LABEL_H_
#pragma once

#include "GUI/Styles.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"
#include "TextWidget.h"

namespace alviz::gui {
class Label : public TextWidget {
 public:
  void render(ICanvas& canvas) override;
  [[nodiscard]] std::string getText() const;

 private:
  std::string _text;
  styles::TextStyle _style;
};
}  // namespace alviz::gui

#endif  // ALGOVIZ_GUI_LABEL_H_
