#ifndef OPTIONS_H
#define OPTIONS_H
#include <SFML/Window/Event.hpp>
#pragma once

#include "main_menu.h"
#include "main_window.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define NUMBER_OF_OPTIONS 3

class Options : public Screen {
private:
  Screen **current_screen;
  MainMenu *main_menu;
  int selected_options_index;
  sf::Text options_options[NUMBER_OF_OPTIONS];
  sf::Font open_sans;
  int selected_option;

public:
  Options(Screen **screen_ptr, MainMenu *menu);
  ~Options();

  void draw(sf::RenderWindow &window) override;
  void move_up() override;
  void move_down() override;
  void move_left() override;
  void move_right() override;
  int pressed() override { return selected_option; }
  void change_option(int selected) override;
  void drop_down(int option) override;
  void typed_on(sf::Event input) override;
};

#endif
