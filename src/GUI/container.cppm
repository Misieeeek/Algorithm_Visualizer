module;

#include <cstddef>
#include <memory>
#include <vector>

export module GUI.Container;

import std;
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
  void update(math::f32 deltaTime) override;
  void render(ICanvas& canvas) override;
  void onKey(Key key) override;
  void onText(math::u32 unicode) override;
  void onMouseMove(Vec2i pos) override;
  void onMouseClick(Vec2i pos) override;

 private:
  std::shared_ptr<Widget> getFocused();
  void setFocus(std::shared_ptr<Widget>& widget);
  void nextFocus();

  std::vector<std::shared_ptr<Widget>> children_;
  static constexpr size_t kNoFocus = std::numeric_limits<size_t>::max();
  size_t focusIndex_ = kNoFocus;
  Layout layout_;
};
}  // namespace alviz::gui
