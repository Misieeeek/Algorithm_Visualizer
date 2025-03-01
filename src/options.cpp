#include "options.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include <string>
#include "main_menu.h"
#include "main_window.h"

Options::Options(Screen** screen_ptr, MainMenu* menu)
    : m_selected_options_index(0) {

  current_screen = screen_ptr;
  main_menu = menu;

  std::array<std::string, NUMBER_OF_OPTIONS> options = {"Speed", "Window",
                                                        "Back"};
  Screen::set_sf_text_style(m_options_options, options, 70, 50, 150, false,
                            true, 0, 100);
  m_options_options[NUMBER_OF_OPTIONS - 1].setFillColor(sf::Color::Red);
  m_options_options[0].setFillColor(sf::Color::Green);
  m_selected_option = 0;
}

Options::~Options() {}

void Options::move_up() {
  if (m_selected_options_index - 1 >= 0) {
    if (m_selected_options_index == NUMBER_OF_OPTIONS - 1)
      m_options_options[m_selected_options_index].setFillColor(sf::Color::Red);
    else
      m_options_options[m_selected_options_index].setFillColor(
          sf::Color::White);
    m_selected_options_index--;
    m_options_options[m_selected_options_index].setFillColor(sf::Color::Green);
    m_selected_option = m_selected_options_index;
  }
}

void Options::move_down() {
  if (m_selected_options_index + 1 < NUMBER_OF_OPTIONS) {
    m_options_options[m_selected_options_index].setFillColor(sf::Color::White);
    m_selected_options_index++;
    m_options_options[m_selected_options_index].setFillColor(sf::Color::Green);
    m_selected_option = m_selected_options_index;
  }
}

void Options::draw(sf::RenderWindow& window) {
  for (const auto& x : m_options_options)
    window.draw(x);
}

void Options::change_option(int selected) {
  switch (selected) {
    case 0:
      break;
    case 1:
      break;
    case 2:
      *current_screen = main_menu;
      break;
  }
}

void Options::drop_down(int option) {}
void Options::typed_on(sf::Event input) {}
void Options::move_left() {}
void Options::move_right() {}
