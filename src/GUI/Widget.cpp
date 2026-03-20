#include "GUI/Widget.h"

namespace alviz::gui {
void Widget::update() {}

void Widget::onKey(Key key) {}

void Widget::onText(uint32_t unicode) {}

void Widget::onMouseMove(float xPos, float yPos) {}

void Widget::onMouseClick(float xPos, float yPos) {}

bool Widget::contains(float xPos, float yPos) {
  return _bounds.contains(xPos, yPos);
}

bool Widget::visible() const { return _visible; }

void Widget::setFocused(bool isFocused) { _focused = isFocused; }

bool Widget::getFocused() const { return _focused; }

}  // namespace alviz::gui
