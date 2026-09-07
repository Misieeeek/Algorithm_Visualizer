module;

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Window.hpp"

module GUI.Widget;

import Alviz.Math;
import GUI.Key;

namespace alviz::gui {
void Widget::onKey(Key key) {}

void Widget::onText(math::u32 unicode) {}

void Widget::update(math::f32 deltaTime) {}

void Widget::onMouseMove(Vec2i pos) {}

void Widget::onMouseClick(Vec2i pos) {}

bool Widget::contains(Vec2i pos) const {
  return bounds_.contains(static_cast<math::f32>(pos.y),
                          static_cast<math::f32>(pos.y));
}

void Widget::setVisible(bool visibility) { visible_ = visibility; }

bool Widget::visible() const { return visible_; }

void Widget::setFocused(bool isFocused) { focused_ = isFocused; }

bool Widget::getFocused() const { return focused_; }

void Widget::setBounds(FloatRect bounds) { bounds_ = bounds; }

FloatRect Widget::getBounds() const { return bounds_; }

}  // namespace alviz::gui
