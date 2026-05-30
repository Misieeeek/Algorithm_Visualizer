module;

module GUI.Button;

import std;
import GUI.Styles;
import GUI.Common;

namespace alviz::gui {
void Button::render(ICanvas& canvas) {
  Color background = getFocused() ? style_.focused : style_.normal;
  canvas.drawRect(getBounds(), background);
  canvas.drawBorder(getBounds(), style_.border, style_.borderThickness);
  canvas.drawText(getText(), {getBounds().x + 8, getBounds().y + 8},
                  style_.text, style_.fontSize, style_.style);
}

void Button::press() {
  if (onClick_) {
    onClick_();
  }
}

void Button::setOnPress(std::function<void()> callback) {
  onClick_ = std::move(callback);
}

void Button::onMouseClick(math::f32 xPos, math::f32 yPos) {
  if (contains(xPos, yPos)) {
    press();
  }
}

void Button::onKey(Key key) {
  if (key == Key::Enter && getFocused()) {
    press();
  }
}

}  // namespace alviz::gui
