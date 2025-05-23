#ifndef GLOBAL_OPTIONS_H
#define GLOBAL_OPTIONS_H
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include <memory>
#include "main_menu.h"
#include "main_window.h"

class Options : public Screen {
 public:
  Options(std::shared_ptr<Screen>& screen_ptr, std::shared_ptr<MainMenu> menu);

  ~Options() = default;

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
  std::shared_ptr<Screen>& current_screen;
  std::shared_ptr<MainMenu> main_menu;
  int m_selected_options_index;
  static constexpr size_t c_number_of_options = 3;
  std::array<sf::Text, c_number_of_options> m_options_options;
  int m_selected_option;
};

#endif
