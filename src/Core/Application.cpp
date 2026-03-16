#include "Core/Application.h"

#include <SFML/Window/Event.hpp>

namespace alviz {
void Application::run() {
  createScreen();
  while (_window.isOpen()) {
    handleEvents();
    render();
  }
}

void Application::createScreen() {
  _window.create(sf::VideoMode({_width, _height}), _name,
                 sf::Style::Close | sf::Style::Resize);
}

void Application::handleEvents() {
  while (const std::optional EVENT = _window.pollEvent()) {
  }
}

void Application::render() {
  _window.clear();
  _window.display();
}

}  // namespace alviz
