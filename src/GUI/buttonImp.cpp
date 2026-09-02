module;

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

module GUI.Button;

import std;
import GUI.Styles;
import GUI.Common;

namespace alviz::gui {
namespace math = alviz::math;
void Button::render(ICanvas& canvas) {
  Color background = style_.normal;
  if (getFocused()) {
    background = style_.focused;
  } else if (hovered_) {
    background = style_.hovered;
  }
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

void Button::onButtonPressed(const sf::Event::MouseButtonPressed& evnt) {
  std::cout << "Test\n";
  if (evnt.button != sf::Mouse::Button::Left) return;
  if (onClick_) onClick_();
}

void Button::onMouseClick(Vec2i pos) {
  if (contains(pos.x, pos.y)) {
    press();
  }
}

void Button::onMouseHover(Vec2i pos) { hovered_ = contains(pos.x, pos.y); }

void Button::onKey(Key key) {
  if (key == Key::Enter && getFocused()) {
    press();
  }
}

void Button::onMouseMove(Vec2i pos) { std::cout << "xd\n"; }
}  // namespace alviz::gui
