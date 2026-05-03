module;

#include <cstddef>
#include <memory>
#include <vector>

export module GUI.Container;

import GUI.ICanvas;
import Alviz.Math;
import GUI.Widget;

export namespace alviz::gui {

namespace math = alviz::math;

enum class Layout { Vertical, Horizontal, Grid, Absolute };

class Container : public Widget {
 public:
  void add(const std::shared_ptr<Widget> widget);
  void remove(const std::shared_ptr<Widget> widget);
  void update() override;
  void render(ICanvas& canvas) override;
  void onKey(Key key) override;
  void onText(math::u32 unicode) override;
  void onMouseMove(math::f32 xPos, math::f32 yPos) override;
  void onMouseClick(math::f32 xPos, math::f32 yPos) override;

 private:
  std::shared_ptr<Widget> getFocused_();
  void setFocus_(std::shared_ptr<Widget>& widget);
  void nextFocus_();

  std::vector<std::shared_ptr<Widget>> children_;
  size_t focusIndex_ = 1;
  Layout layout_;
};
}  // namespace alviz::gui
