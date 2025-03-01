#include "main_menu.h"
#include <SFML/Window/Event.hpp>
#include <array>
#include <filesystem>

MainMenu::MainMenu() : m_selected_item_index(0) {
  std::array<std::string, NUMBER_OF_ITEMS> options = {"Visualize", "Options",
                                                      "Exit"};
  Screen::set_sf_text_style(m_main_menu_options, options, 70, 50, 150, false,
                            true, 0, 100);
  m_main_menu_options[NUMBER_OF_ITEMS - 1].setFillColor(sf::Color::Red);
  m_main_menu_options[0].setFillColor(sf::Color::Green);
  m_selected = 0;
}

MainMenu::~MainMenu() {}

void MainMenu::move_up() {
  if (m_selected_item_index - 1 >= 0) {
    if (m_selected_item_index == NUMBER_OF_ITEMS - 1)
      m_main_menu_options[m_selected_item_index].setFillColor(sf::Color::Red);
    else
      m_main_menu_options[m_selected_item_index].setFillColor(sf::Color::White);
    m_selected_item_index--;
    m_main_menu_options[m_selected_item_index].setFillColor(sf::Color::Green);
    m_selected = m_selected_item_index;
  }
}

void MainMenu::move_down() {
  if (m_selected_item_index + 1 < NUMBER_OF_ITEMS) {
    m_main_menu_options[m_selected_item_index].setFillColor(sf::Color::White);
    m_selected_item_index++;
    m_main_menu_options[m_selected_item_index].setFillColor(sf::Color::Green);
    m_selected = m_selected_item_index;
  }
}

void MainMenu::draw(sf::RenderWindow& window) {
  for (const auto& x : m_main_menu_options)
    window.draw(x);
}
