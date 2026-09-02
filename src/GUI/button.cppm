module;

#include <SFML/Window/Event.hpp>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"

export module GUI.Button;

import std;
import Alviz.Math;
import Alviz.Events;
import GUI.Styles;
import GUI.ICanvas;
import GUI.Label;

export namespace alviz::gui {
using namespace alviz::math;
class Button : public Label, public IMouseListener {
 public:
  void render(ICanvas& canvas) override;
  void setOnPress(std::function<void()> callback);
  void onButtonPressed(const sf::Event::MouseButtonPressed& evnt);
  void onMouseClick(Vec2i pos) override;
  void onMouseMove(Vec2i pos) override;
  void onMouseHover(Vec2i pos);
  void onKey(Key key) override;
  void press();

 private:
  ListenerConnection connection_;
  std::function<void()> onClick_;
  styles::ButtonStyle style_;
  bool hovered_{false};
};
}  // namespace alviz::gui
