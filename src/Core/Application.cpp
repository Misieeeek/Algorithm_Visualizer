#include "Core/Application.h"

#include "SFML/Window/Event.hpp"

namespace alviz {
void Application::run() {
  _window.create(sf::VideoMode(1280, 720), "Algorithm Visualizer",
                 sf::Style::Close | sf::Style::Resize);
  while (_window.isOpen()) {
    handleEvents();
    render();
  }
}

void Application::handleEvents() {
  sf::Event evnt;
  while (_window.pollEvent(evnt)) {
    if (evnt.type == sf::Event::Closed) {
      _window.close();
    }
  }
}

void Application::render() {
  _window.clear();
  _window.display();
}

}  // namespace alviz
