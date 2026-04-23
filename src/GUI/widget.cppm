module;

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Window.hpp"

export module GUI.Widget;

import GUI.ICanvas;

export namespace alviz::gui {
class Widget {
 public:
  virtual ~Widget() = default;

  virtual void render(ICanvas& canvas) = 0;

  virtual void update();
  virtual void onKey(Key key);
  virtual void onText(uint32_t unicode);
  virtual void onMouseMove(float xPos, float yPos);
  virtual void onMouseClick(float xPos, float yPos);

  bool contains(float xPos, float yPos);
  [[nodiscard]] bool visible() const;

  void setFocused(bool isFocused);
  [[nodiscard]] bool getFocused() const;

  void setBounds(FloatRect bounds);
  [[nodiscard]] FloatRect getBounds() const;

 private:
  FloatRect _bounds;
  bool _visible = true;
  bool _focused = false;
};
}  // namespace alviz::gui
