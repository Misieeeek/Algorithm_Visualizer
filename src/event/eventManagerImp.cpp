module;

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

module Alviz.EventManager;

import std;
import Alviz.Utils;

namespace alviz {
void EventManager::pollAndDispatch(sf::RenderWindow& window) {
  while (const std::optional event = window.pollEvent()) {
    event->visit(Overloaded{[this](const sf::Event::Closed&) {
                              notifyWindowListeners(WindowEvent::CLOSED);
                            },
                            [this](const sf::Event::Resized&) {
                              notifyWindowListeners(WindowEvent::RESIZED);
                            },
                            [this](const sf::Event::FocusLost&) {
                              notifyWindowListeners(WindowEvent::FOCUSLOST);
                            },
                            [this](const sf::Event::FocusGained&) {
                              notifyWindowListeners(WindowEvent::FOCUSGAINED);
                            },
                            [this](const sf::Event::KeyPressed& evnt) {
                              for (auto* listener : keyboardListeners_) {
                                listener->onKeyPressed(evnt);
                              }
                            },
                            [this](const sf::Event::MouseButtonPressed& evnt) {
                              for (auto* listener : mouseListeners_) {
                                listener->onButtonPressed(evnt);
                              }
                            },
                            [](const auto&) {}});
  }
}

ListenerConnection EventManager::addKeyboardListener(
    IKeyboardListener& keyboard) {
  keyboardListeners_.push_back(&keyboard);

  return ListenerConnection(
      [this, &keyboard]() { std::erase(keyboardListeners_, &keyboard); });
}

ListenerConnection EventManager::addMouseListener(IMouseListener& mouse) {
  mouseListeners_.push_back(&mouse);

  return ListenerConnection(
      [this, &mouse]() { std::erase(mouseListeners_, &mouse); });
}

ListenerConnection EventManager::addWindowListener(IWindowListener& window) {
  windowListeners_.push_back(&window);

  return ListenerConnection(
      [this, &window]() { std::erase(windowListeners_, &window); });
}

void EventManager::notifyWindowListeners(WindowEvent evnt) {
  for (auto* listener : windowListeners_) {
    switch (evnt) {
      case WindowEvent::CLOSED:
        listener->onWindowClosed();
        break;
      case WindowEvent::FOCUSLOST:
        listener->onFocusLost();
        break;
      case WindowEvent::FOCUSGAINED:
        listener->onFocusGained();
        break;
      case WindowEvent::RESIZED:
        break;
    }
  }
}
}  // namespace alviz
