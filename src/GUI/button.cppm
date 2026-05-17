module;

#include <functional>
#include <string>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"

export module GUI.Button;

import Alviz.Math;
import GUI.Styles;
import GUI.ICanvas;
import GUI.Label;

export namespace alviz::gui {
namespace math = alviz::math;

class Button : public Label {
 public:
  void render(ICanvas& canvas) override;
  void setOnPress(std::function<void()> callback);
  void onMouseClick(math::f32 xPos, math::f32 yPos) override;
  void onKey(Key key) override;
  void press();

 private:
  std::function<void()> onClick_;
  styles::ButtonStyle style_;
};
}  // namespace alviz::gui
