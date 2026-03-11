#include "core/application.h"

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
  _window.create(sf::VideoMode(_width, _height), _name,
                 sf::Style::Close | sf::Style::Resize);
}

void Application::handleEvents() {
  sf::Event evnt;
  while (_window.pollEvent(evnt)) {
    switch (evnt.type) {
      case sf::Event::Closed:
        _window.close();
        break;
      case sf::Event::TextEntered:

        break;
      case sf::Event::KeyPressed:

        break;
    }
  }
}

void Application::render() {
  _window.clear();
  _window.display();
}

}  // namespace alviz
