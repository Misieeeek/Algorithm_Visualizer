module;

module GUI.Input;

import std;
import GUI.ICanvas;

namespace alviz::gui {
void Input::render(ICanvas& canvas) {
  canvas.drawRect(getBounds(), colorRect_);
  const std::string& display = text_.empty() ? placeholder_ : text_;
  Color textColor = text_.empty()
                        ? Color{.r = 150, .g = 150, .b = 150, .a = 255}
                        : colorText_;

  canvas.drawText(display, {getBounds().x + 4, getBounds().y + 4}, textColor);
  if (getFocused() && cursorVisible_) {
    canvas.drawCursor(getBounds(), text_);
  }
}

void Input::update(math::f32 deltaTime) {
  cursorTimer_ += deltaTime;
  if (cursorTimer_ >= 0.5F) {
    cursorVisible_ = !cursorVisible_;
    cursorTimer_ = 0.F;
  }
}

void Input::onText(math::u32 unicode) {
  if (!getFocused()) {
    return;
  }

  if (unicode == '\b') {
    if (!text_.empty()) {
      text_.pop_back();
    }
  } else {
    text_ += static_cast<char>(unicode);
  }
  onTextChanged();
}

void Input::onMouseMove(math::f32 xPos, math::f32 yPos) {}

void Input::onMouseClick(math::f32 xPos, math::f32 yPos) {
  setFocused(contains(xPos, yPos));
}

void Input::setPlaceholder(std::string placeholder) {
  placeholder_ = std::move(placeholder);
}

const std::string& Input::getText() const { return text_; }

void Input::clear() { text_.clear(); }

void Input::onTextChanged() {}

}  // namespace alviz::gui
