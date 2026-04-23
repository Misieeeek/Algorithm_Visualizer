import GUI.Button;

namespace alviz::gui {
void Button::render(ICanvas& canvas) {
  Color background = getFocused() ? _style.focused : _style.normal;
  canvas.drawRect(getBounds(), background);
  canvas.drawBorder(getBounds(), _style.border, _style.borderThickness);
  canvas.drawText(_text, {getBounds().x + 8, getBounds().y + 8}, _style.text,
                  _style.fontSize, _style.style);
}

void Button::press() {
  if (_onClick) {
    _onClick();
  }
}

void Button::setOnPress(std::function<void()> callback) {
  _onClick = std::move(callback);
}

void Button::onMouseClick(float xPos, float yPos) {
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
