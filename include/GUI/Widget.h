#ifndef ALGOVIZ_GUI_WIDGETFACTORY_H_
#define ALGOVIZ_GUI_WIDGETFACTORY_H_
#pragma once

#include "ICanvas.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Window.hpp"

namespace alviz::gui {
class Widget {
 public:
  virtual ~Widget() = default;

  virtual void render(ICanvas& canvas) = 0;

  virtual void update();
  virtual void onKey(Key key);
  virtual void onText(uint32_t unicode);
  virtual void onMouseMove(float xPos, float yPos);
  virtual void onMouseClick(float xPos, float yPos);

  bool contains(float xPos, float yPos);
  [[nodiscard]] bool visible() const;

  void setFocused(bool isFocused);
  [[nodiscard]] bool getFocused() const;

 private:
  FloatRect _bounds;
  bool _visible = true;
  bool _focused = false;
};
}  // namespace alviz::gui

#endif  // ALGOVIZ_GUI_WIDGETFACTORY_H_
