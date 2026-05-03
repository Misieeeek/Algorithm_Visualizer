module;

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"

export module GUI.TextWidget;

import GUI.ICanvas;
import GUI.Widget;

export namespace alviz::gui {
class TextWidget : public Widget {
 public:
  void render(ICanvas& canvas) override;

 private:
};
}  // namespace alviz::gui
