module;

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Window.hpp"

module GUI.Widget;

import Alviz.Math;

namespace alviz::gui {
void Widget::update(math::f32 deltaTime) {}

void Widget::onKey(Key key) {}

void Widget::onText(math::u32 unicode) {}

void Widget::onMouseMove(math::f32 xPos, math::f32 yPos) {}

void Widget::onMouseClick(math::f32 xPos, math::f32 yPos) {}

bool Widget::contains(math::f32 xPos, math::f32 yPos) const {
  return bounds_.contains(xPos, yPos);
}

void Widget::setVisible(bool visibility) { visible_ = visibility; }

bool Widget::visible() const { return visible_; }

void Widget::setFocused(bool isFocused) { focused_ = isFocused; }

bool Widget::getFocused() const { return focused_; }

void Widget::setBounds(FloatRect bounds) { bounds_ = bounds; }

FloatRect Widget::getBounds() const { return bounds_; }

}  // namespace alviz::gui
