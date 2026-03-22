#include "GUI/Button.h"

namespace alviz::gui {
void Button::render(ICanvas& canvas) {
  Color bg = getFocused() ? _style.focused : _style.normal;
  canvas.drawRect(getBounds(), bg);
  canvas.drawBorder(getBounds(), _style.border, _style.borderThickness);
  canvas.drawText(_text, {getBounds().x + 8, getBounds().y + 8}, _style.text,
                  _style.fontSize, _style.style);
}
}  // namespace alviz::gui
