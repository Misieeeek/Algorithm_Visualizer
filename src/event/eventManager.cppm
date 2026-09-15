module;

#include <SFML/Graphics/RenderWindow.hpp>
#include <cstddef>

export module Alviz.EventManager;

import Alviz.Events;

export namespace alviz {
class EventManager {
 public:
  void pollAndDispatch(sf::RenderWindow& window);
  [[nodiscard]] ListenerConnection addKeyboardListener(
      IKeyboardListener& keyboard);
  [[nodiscard]] ListenerConnection addMouseListener(IMouseListener& mouse);
  [[nodiscard]] ListenerConnection addWindowListener(IWindowListener& window);
  [[nodiscard]] std::size_t keyboardListenersCount() const noexcept;
  [[nodiscard]] std::size_t mouseListenersCount() const noexcept;
  [[nodiscard]] std::size_t windowListenersCount() const noexcept;

 private:
  void notifyWindowListeners(WindowEvent evnt);

  std::vector<IKeyboardListener*> keyboardListeners_;
  std::vector<IWindowListener*> windowListeners_;
  std::vector<IMouseListener*> mouseListeners_;
};
}  // namespace alviz
