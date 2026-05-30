module;

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <string>

module Alviz.App;

import Alviz.ResourceManager;
import GUI.CanvasSFML;
import GUI.Button;
import GUI.Container;

namespace alviz {
void App::run() {
  loadResources();
  createScreen();
  while (window_.isOpen()) {
    handleEvents();
    render();
  }
}

void App::createScreen() {
  window_.create(sf::VideoMode({width_, height_}), name_,
                 sf::Style::Close | sf::Style::Resize);
  auto btn = std::make_shared<gui::Button>();
  btn->setBounds({100.F, 50.F, 120.F, 80.F});
  btn->setStyle({});
  btn->setText("First debug button");
  mainContainer_.add(btn);
}

void App::handleEvents() {
  while (const std::optional EVENT = window_.pollEvent()) {
  }
}

void App::render() {
  window_.clear();
  gui::CanvasSFML canvas(window_, font_);
  mainContainer_.render(canvas);
  window_.display();
}

void App::loadResources() {
  ResourceManager resourceManager;
  std::string filename{"OpenSans-Regular.ttf"};
  resourceManager.loadFont(font_, filename);
}

}  // namespace alviz
