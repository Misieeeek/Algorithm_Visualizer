module;

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Window.hpp"

export module GUI.Widget;

import Alviz.Math;
import GUI.ICanvas;

export namespace alviz::gui {
namespace math = alviz::math;

class Widget {
 public:
  virtual ~Widget() = default;

  virtual void render(ICanvas& canvas) = 0;

  virtual void update();
  virtual void onKey(Key key);
  virtual void onText(math::u32 unicode);
  virtual void onMouseMove(math::f32 xPos, math::f32 yPos);
  virtual void onMouseClick(math::f32 xPos, math::f32 yPos);

  bool contains(math::f32 xPos, math::f32 yPos);
  [[nodiscard]] bool visible() const;

  void setFocused(bool isFocused);
  [[nodiscard]] bool getFocused() const;

  void setBounds(FloatRect bounds);
  [[nodiscard]] FloatRect getBounds() const;

 private:
  FloatRect bounds_;
  bool visible_ = true;
  bool focused_ = false;
};
}  // namespace alviz::gui
