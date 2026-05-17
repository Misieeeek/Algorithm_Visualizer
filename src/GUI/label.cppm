module;

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"

export module GUI.Label;

import std;
import GUI.ICanvas;
import Alviz.Math;
import GUI.Styles;
import GUI.Widget;

export namespace alviz::gui {
class Label : public Widget {
 public:
  void render(ICanvas& canvas) override;
  void setText(std::string text);
  [[nodiscard]] const std::string& getText() const;

 private:
  std::string text_;
  styles::LabelStyle style_;
};
}  // namespace alviz::gui
