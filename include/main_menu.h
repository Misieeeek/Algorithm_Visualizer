#ifndef MAINMENU_H
#define MAINMENU_H
#include <SFML/Window/Event.hpp>
#pragma once

#include "main_window.h"
#include <iostream>

#define NUMBER_OF_ITEMS 3

class MainMenu : public Screen {
private:
  int selected_item_index;
  sf::Text main_menu_options[NUMBER_OF_ITEMS];
  sf::Font open_sans;
  int selected;

public:
  MainMenu();
  ~MainMenu();

  void draw(sf::RenderWindow &window) override;
  void move_up() override;
  void move_down() override;
  void move_left() override;
  void move_right() override;
  int pressed() override { return selected; }
  void change_option(int selected) override;

  void drop_down(int option) override;
  void typed_on(sf::Event input) override;
};

#endif
