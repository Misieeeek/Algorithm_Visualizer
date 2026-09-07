module;

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"

export module GUI.Input;

import std;
import GUI.ICanvas;
import GUI.Common;
import GUI.Widget;
import Alviz.Math;

export namespace alviz::gui {
class Input : public Widget {
 public:
  void render(ICanvas& canvas) override;
  void update(math::f32 deltaTime) override;
  void onText(math::u32 unicode) override;
  void onMouseMove(Vec2i pos) override;
  void onMouseClick(Vec2i pos) override;

  void setPlaceholder(std::string placeholder);
  [[nodiscard]] const std::string& getText() const;

  void clear();

 protected:
  virtual void onTextChanged();

 private:
  std::string text_;
  std::string placeholder_;
  bool cursorVisible_{true};
  math::f32 cursorTimer_{0.F};
  Color colorText_;
  Color colorRect_;
};
}  // namespace alviz::gui
