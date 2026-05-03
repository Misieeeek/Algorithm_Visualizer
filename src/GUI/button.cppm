module;

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"

export module GUI.Button;

import std;
import Alviz.Math;
import GUI.ICanvas;
import GUI.Label;
import GUI.TextWidget;

export namespace alviz::gui {
using math = alviz::math;

class Button : public TextWidget {
 public:
  void render(ICanvas& canvas) override;
  void setOnPress(std::function<void()> callback);
  void onMouseClick(math::f32 xPos, math::f32 yPos) override;
  void onKey(Key key) override;
  void press();

 private:
  std::function<void()> onClick_;
  styles::ButtonStyle style_;
  std::string text_;
};
}  // namespace alviz::gui
