module;

export module GUI.Widget;

import Alviz.Math;
import GUI.ICanvas;

export namespace alviz::gui {
namespace math = alviz::math;

class Widget {
 public:
  virtual ~Widget() = default;

  virtual void render(ICanvas& canvas) = 0;

  virtual void update(math::f32 deltaTime);
  virtual void onKey(Key key);
  virtual void onText(math::u32 unicode);
  virtual void onMouseMove(Vec2i pos);
  virtual void onMouseClick(Vec2i pos);

  [[nodiscard]] bool contains(Vec2i pos) const;

  void setVisible(bool visibility);
  [[nodiscard]] bool visible() const;

  void setFocused(bool isFocused);
  [[nodiscard]] bool getFocused() const;

  void setBounds(FloatRect bounds);
  [[nodiscard]] FloatRect getBounds() const;

 private:
  FloatRect bounds_{};
  bool visible_{true};
  bool focused_{false};
};
}  // namespace alviz::gui
