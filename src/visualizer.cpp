#include "visualizer.h"
#include "main_menu.h"
#include "main_window.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>

Visualizer::Visualizer(Screen **screen_ptr, MainMenu *menu)
    : selected_algorithm_index(0) {

  std::filesystem::current_path(
      std::filesystem::path(__FILE__).parent_path().parent_path());

  if (!open_sans.loadFromFile("assets/fonts/OpenSans-Regular.ttf")) {
    std::cerr << "Failed to load font" << std::endl;
  }

  current_screen = screen_ptr;
  main_menu = menu;

  std::string algo[] = {"Sorting Algorithms",
                        "Searching Algorithms",
                        "Data Structures",
                        "Dynamic Programming",
                        "Greedy Algorithms",
                        "Advanced Data Structures",
                        "Back"};

  for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setFont(open_sans);
    list_algorithms[i].setFillColor(sf::Color::White);
    list_algorithms[i].setCharacterSize(35);
    list_algorithms[i].setStyle(sf::Text::Bold);
    list_algorithms[i].setPosition(50, 50 * i + 150);
    list_algorithms[i].setString(algo[i]);
  }
  list_algorithms[NUMBER_OF_ALGORITHMS - 1].setFillColor(sf::Color::Red);
  list_algorithms[0].setFillColor(sf::Color::Green);
  selected_algorithm = 0;
}

Visualizer::~Visualizer() {}

void Visualizer::move_up() {
  if (selected_algorithm_index - 1 >= 0) {
    if (selected_algorithm_index == NUMBER_OF_ALGORITHMS - 1)
      list_algorithms[selected_algorithm_index].setFillColor(sf::Color::Red);
    else
      list_algorithms[selected_algorithm_index].setFillColor(sf::Color::White);
    selected_algorithm_index--;
    list_algorithms[selected_algorithm_index].setFillColor(sf::Color::Green);
    selected_algorithm = selected_algorithm_index;
  }
}

void Visualizer::move_down() {
  if (selected_algorithm_index + 1 < NUMBER_OF_ALGORITHMS) {
    list_algorithms[selected_algorithm_index].setFillColor(sf::Color::White);
    selected_algorithm_index++;
    list_algorithms[selected_algorithm_index].setFillColor(sf::Color::Green);
    selected_algorithm = selected_algorithm_index;
  }
}

void Visualizer::draw(sf::RenderWindow &window) {
  for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++)
    window.draw(list_algorithms[i]);
}

void Visualizer::setState(State new_state) { current_state = new_state; }

void Visualizer::change_option(int selected) {
  switch (selected) {
  case 0:
    (*current_screen)->setState(Screen::State::VISUALIZESCREEN);
    break;
  case 1:
    (*current_screen)->setState(Screen::State::VISUALIZESCREEN);
    break;
  case 6:
    selected = -1;
    *current_screen = main_menu;
    (*current_screen)->setState(Screen::State::MAINMENU);
    break;
  }
}
