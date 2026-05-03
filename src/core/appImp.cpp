module;

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <string>

module Alviz.App;

import GUI.Button;
import GUI.Container;

namespace alviz {
void App::run() {
  createScreen_();
  while (window_.isOpen()) {
    handleEvents_();
    render_();
  }
}

void App::createScreen_() {
  window_.create(sf::VideoMode({width_, height_}), name_,
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
