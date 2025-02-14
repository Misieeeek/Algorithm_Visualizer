#ifndef VISUALIZER_H
#define VISUALIZER_H
#pragma once

#include "main_menu.h"
#include "main_window.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define NUMBER_OF_ALGORITHMS 7

class Visualizer : public Screen {
private:
  Screen **current_screen;
  MainMenu *main_menu;
  int selected_algorithm_index;
  sf::Text list_algorithms[NUMBER_OF_ALGORITHMS];
  sf::Font open_sans;
  int selected_algorithm;

public:
  Visualizer(Screen **screen_ptr, MainMenu *menu);
  ~Visualizer();

  void draw(sf::RenderWindow &window) override;
  void move_up() override;
  void move_down() override;
  int pressed() override { return selected_algorithm; }
  void change_option(int selected) override;
  void setState(State newState) override;
};

#endif
