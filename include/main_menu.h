#ifndef MAINMENU_H
#define MAINMENU_H
#pragma once

#include <SFML/Window/Event.hpp>
#include <array>
#include <iostream>
#include "main_window.h"

#define NUMBER_OF_ITEMS 3

class MainMenu : public Screen {
 public:
  MainMenu();
  ~MainMenu();

  void draw(sf::RenderWindow& window) override;
  void move_up() override;
  void move_down() override;
  int pressed() override { return m_selected; }

 private:
  int m_selected_item_index;
  std::array<sf::Text, NUMBER_OF_ITEMS> m_main_menu_options;
  int m_selected;
};

#endif
