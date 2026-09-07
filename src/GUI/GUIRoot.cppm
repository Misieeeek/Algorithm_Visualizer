module;

#include <SFML/Window/Event.hpp>

export module GUI.Root;

import std;
import Alviz.Math;
import Alviz.Events;
import Alviz.EventManager;
import GUI.Widget;
import GUI.ICanvas;
import GUI.Container;

export namespace alviz::gui {
class GUIRoot : public IMouseListener, public IKeyboardListener {
 public:
  GUIRoot(EventManager& events);

  void onKeyPressed(const sf::Event::KeyPressed& evnt) override;
  void onMouseMove(const sf::Event::MouseMoved& evnt) override;
  void onButtonPressed(const sf::Event::MouseButtonPressed& evnt) override;

  void add(std::shared_ptr<Widget> widget) { root_.add(std::move(widget)); }
  void render(ICanvas& canvas) { root_.render(canvas); }
  void update(math::f32 dt) { root_.update(dt); }

 private:
  Container root_;
  ListenerConnection mouseConn_, keyboardConn_;
};
}  // namespace alviz::gui
