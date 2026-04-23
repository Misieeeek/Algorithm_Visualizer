#include "Core/Application.h"

#include <SFML/Window/Event.hpp>

#include "GUI/Button.h"
#include "GUI/Container.h"
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
  gui::Container con;
  auto btn = std::make_shared<gui::Button>();
  con.add(btn);
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
