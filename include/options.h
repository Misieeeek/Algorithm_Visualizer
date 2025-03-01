#ifndef OPTIONS_H
#define OPTIONS_H
#include <SFML/Graphics/Text.hpp>
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include "main_menu.h"
#include "main_window.h"

#define NUMBER_OF_OPTIONS 3

class Options : public Screen {
 public:
  Options(Screen** screen_ptr, MainMenu* menu);
  ~Options();

  void draw(sf::RenderWindow& window) override;
  void move_up() override;
  void move_down() override;
  int pressed() override { return m_selected_option; }
  void change_option(int selected) override;

  // CURRENTLY NOT USED, BUT CERTAINLY WILL BE USED IN THE FUTURE
  void drop_down(int option) override;
  void typed_on(sf::Event input) override;
  void move_left() override;
  void move_right() override;

 private:
  Screen** current_screen;
  MainMenu* main_menu;
  int m_selected_options_index;
  std::array<sf::Text, NUMBER_OF_OPTIONS> m_options_options;
  int m_selected_option;
};

#endif
