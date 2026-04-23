module;

#include <functional>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"

export module GUI.Button;

import GUI.ICanvas;
import GUI.Label;
import GUI.TextWidget;

export namespace alviz::gui {
class Button : public TextWidget {
 public:
  void render(ICanvas& canvas) override;
  void setOnPress(std::function<void()> callback);
  void onMouseClick(float xPos, float yPos) override;
  void onKey(Key key) override;
  void press();

 private:
  std::function<void()> _onClick;
  styles::ButtonStyle _style;
  std::string _text;
};
}  // namespace alviz::gui
