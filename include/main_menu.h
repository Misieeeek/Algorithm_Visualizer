#ifndef MAINMENU_H
#define MAINMENU_H
#pragma once

#include <SFML/Window/Event.hpp>
#include <array>
#include <iostream>
#include "main_window.h"

class MainMenu : public Screen {
 public:
  MainMenu();
  ~MainMenu();

  void draw(sf::RenderWindow& window) override;
  void move_up() override;
  void move_down() override;
  int pressed() override { return m_selected; }

 private:
  static constexpr int c_number_of_items = 3;
  int m_selected_item_index = 0;
  std::array<sf::Text, c_number_of_items> m_main_menu_options;
  int m_selected = 0;
};

#endif
