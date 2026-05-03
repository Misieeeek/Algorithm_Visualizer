#include <SFML/Window/Event.hpp>

module Alviz.App;

import GUI.Button;
import GUI.Container;

namespace alviz {
void App::run() {
  createScreen();
  while (window_.isOpen()) {
    handleEvents();
    render();
  }
}

void App::createScreen_() {
  _window.create(sf::VideoMode({width_, height_}), name_,
                 sf::Style::Close | sf::Style::Resize);
  gui::Container con;
  auto btn = std::make_shared<gui::Button>();
  con.add(btn);
}

void App::handleEvents_() {
  while (const std::optional EVENT = window_.pollEvent()) {
  }
}

void App::render_() {
  window_.clear();
  window_.display();
}

}  // namespace alviz
