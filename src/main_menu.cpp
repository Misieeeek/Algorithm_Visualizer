#include "main_menu.h"
#include <SFML/Window/Event.hpp>
#include <filesystem>

MainMenu::MainMenu() : m_selected_item_index(0) {

  std::filesystem::current_path(
      std::filesystem::path(__FILE__).parent_path().parent_path());

  if (!m_open_sans.loadFromFile("assets/fonts/OpenSans-Regular.ttf")) {
    std::cerr << "Failed to load font" << std::endl;
  }

  std::string options[] = {"Visualize", "Options", "Exit"};

  for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
    m_main_menu_options[i].setFont(m_open_sans);
    m_main_menu_options[i].setFillColor(sf::Color::White);
    m_main_menu_options[i].setCharacterSize(70);
    m_main_menu_options[i].setStyle(sf::Text::Bold);
    m_main_menu_options[i].setPosition(50, 100 * i + 150);
    m_main_menu_options[i].setString(options[i]);
  }
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
  for (int i = 0; i < NUMBER_OF_ITEMS; i++)
    window.draw(m_main_menu_options[i]);
}
