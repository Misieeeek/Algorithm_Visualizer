import GUI.Widget;

namespace alviz::gui {
void Widget::update() {}

void Widget::onKey(Key key) {}

void Widget::onText(math::u32 unicode) {}

void Widget::onMouseMove(math::f32 xPos, math::f32 yPos) {}

void Widget::onMouseClick(math::f32 xPos, math::f32 yPos) {}

bool Widget::contains(math::f32 xPos, math::f32 yPos) {
  return bounds_.contains(xPos, yPos);
}

bool Widget::visible() const { return visible_; }

void Widget::setFocused(bool isFocused) { focused_ = isFocused; }

bool Widget::getFocused() const { return focused_; }

}  // namespace alviz::gui
