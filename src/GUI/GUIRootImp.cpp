module;

#include <SFML/Window/Event.hpp>

module GUI.Root;

import std;
import Alviz.Math;
import Alviz.Events;
import Alviz.EventManager;
import GUI.Widget;
import GUI.Container;
import GUI.Key;

namespace alviz::gui {
GUIRoot::GUIRoot(EventManager& events)
    : mouseConn_(events.addMouseListener(*this)),
      keyboardConn_(events.addKeyboardListener(*this)) {}

void GUIRoot::onKeyPressed(const sf::Event::KeyPressed& evnt) {
  root_.onKey(translateKey(evnt.code));
}

void GUIRoot::onMouseMove(const sf::Event::MouseMoved& evnt) {
  Vec2i pos{};
  pos.fromSFML(evnt.position);
  root_.onMouseMove(pos);
}

void GUIRoot::onButtonPressed(const sf::Event::MouseButtonPressed& evnt) {
  Vec2i pos{};
  pos.fromSFML(evnt.position);
  root_.onMouseClick(pos);
}

void GUIRoot::add(std::shared_ptr<Widget> widget) {
  root_.add(std::move(widget));
}

void GUIRoot::render(ICanvas& canvas) { root_.render(canvas); }

void GUIRoot::update(math::f32 dt) { root_.update(dt); }
};  // namespace alviz::gui
