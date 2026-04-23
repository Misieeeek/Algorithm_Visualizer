module;

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"

export module GUI.Label;

import GUI.Styles;
import GUI.TextWidget;

export namespace alviz::gui {
class Label : public TextWidget {
 public:
  void render(ICanvas& canvas) override;
  [[nodiscard]] std::string getText() const;

 private:
  std::string _text;
  styles::TextStyle _style;
};
}  // namespace alviz::gui
