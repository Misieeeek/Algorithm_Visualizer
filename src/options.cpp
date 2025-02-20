#include "options.h"
#include "main_menu.h"
#include "main_window.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>

Options::Options(Screen **screen_ptr, MainMenu *menu)
    : selected_options_index(0) {

  std::filesystem::current_path(
      std::filesystem::path(__FILE__).parent_path().parent_path());

  if (!open_sans.loadFromFile("assets/fonts/OpenSans-Regular.ttf")) {
    std::cerr << "Failed to load font" << std::endl;
  }

  current_screen = screen_ptr;
  main_menu = menu;

  std::string options[] = {"Speed", "Window", "Back"};

  for (int i = 0; i < NUMBER_OF_OPTIONS; i++) {
    options_options[i].setFont(open_sans);
    options_options[i].setFillColor(sf::Color::White);
    options_options[i].setCharacterSize(70);
    options_options[i].setStyle(sf::Text::Bold);
    options_options[i].setPosition(50, 100 * i + 150);
    options_options[i].setString(options[i]);
  }
  options_options[NUMBER_OF_OPTIONS - 1].setFillColor(sf::Color::Red);
  options_options[0].setFillColor(sf::Color::Green);
  selected_option = 0;
}

Options::~Options() {}

void Options::move_up() {
  if (selected_options_index - 1 >= 0) {
    if (selected_options_index == NUMBER_OF_OPTIONS - 1)
      options_options[selected_options_index].setFillColor(sf::Color::Red);
    else
      options_options[selected_options_index].setFillColor(sf::Color::White);
    selected_options_index--;
    options_options[selected_options_index].setFillColor(sf::Color::Green);
    selected_option = selected_options_index;
  }
}

void Options::move_down() {
  if (selected_options_index + 1 < NUMBER_OF_OPTIONS) {
    options_options[selected_options_index].setFillColor(sf::Color::White);
    selected_options_index++;
    options_options[selected_options_index].setFillColor(sf::Color::Green);
    selected_option = selected_options_index;
  }
}

void Options::move_left() {}

void Options::move_right() {}

void Options::draw(sf::RenderWindow &window) {
  for (int i = 0; i < NUMBER_OF_OPTIONS; i++)
    window.draw(options_options[i]);
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
