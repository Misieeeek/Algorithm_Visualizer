#ifndef ALGOVIZ_GUI_CONTAINER_H_
#define ALGOVIZ_GUI_CONTAINER_H_
#pragma once

#include "Widget.h"

namespace alviz::gui {

enum class Layout { Vertical, Horizontal, Grid, Absolute };

class Container : public Widget {
 public:
  void add(std::shared_ptr<Widget>& widget);
  void remove(std::shared_ptr<Widget>& widget);
  void update() override;
  void render(ICanvas& canvas) override;
  void onKey(Key key) override;
  void onText(uint32_t unicode) override;
  void onMouseMove(float xPos, float yPos) override;
  void onMouseClick(float xPos, float yPos) override;

 private:
  std::shared_ptr<Widget> _getFocused();
  void _setFocus(std::shared_ptr<Widget>& widget);
  void _nextFocus();

  std::vector<std::shared_ptr<Widget>> _children;
  size_t _focusIndex = 1;
  Layout _layout;
};
}  // namespace alviz::gui

#endif  // ALGOVIZ_GUI_CONTAINER_H_
