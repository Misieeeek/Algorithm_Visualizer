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

  opend = false;
  current_screen = screen_ptr;
  main_menu = menu;

  std::string algo[] = {"Sorting Algorithms", "Searching Algorithms",
                        "Data Structures",    "Dynamic Programming",
                        "Greedy Algorithms",  "Advanced Data Structures",
                        "Graph Algorithms",   "Back"};

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
  switch (static_cast<int>(ac)) {
  case 0: // SORTING
    window.draw(list_algorithms[0]);
    for (int i = 0; i < NUMBER_OF_SORT_ALGO; i++)
      window.draw(list_algo_sort[i]);
    for (int i = 1; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  default:
    for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
  }
}

void Visualizer::set_state(State new_state) { current_state = new_state; }

void Visualizer::change_option(int selected) {
  switch (selected) {
  case 0:
    if (opend) {
      (*current_screen)->set_state(Screen::State::VISUALIZESCREEN);
      drop_down(selected);
    }
    std::cout << opend << std::endl;
    opend = true;
    break;
  case 1:
    (*current_screen)->set_state(Screen::State::VISUALIZESCREEN);
    drop_down(selected);
    break;
  case 2:
    (*current_screen)->set_state(Screen::State::VISUALIZESCREEN);
    drop_down(selected);
    break;
  case 3:
    (*current_screen)->set_state(Screen::State::VISUALIZESCREEN);
    drop_down(selected);
    break;
  case 4:
    (*current_screen)->set_state(Screen::State::VISUALIZESCREEN);
    drop_down(selected);
    break;
  case 5:
    (*current_screen)->set_state(Screen::State::VISUALIZESCREEN);
    drop_down(selected);
    break;
  case 6:
    (*current_screen)->set_state(Screen::State::VISUALIZESCREEN);
    drop_down(selected);
    break;
  case 7:
    *current_screen = main_menu;
    (*current_screen)->set_state(Screen::State::MAINMENU);
    break;
  }
}

void Visualizer::drop_down(int option) {
  switch (option) {
  case 0:
    ac = Algocat::SORTING;
    sorting_algo_list();
    break;
  case 1:
    ac = Algocat::SEARCHING;
    break;
  case 2:
    ac = Algocat::DS;
    break;
  case 3:
    ac = Algocat::DYNAMIC;
    break;
  case 4:
    ac = Algocat::GREEDY;
    break;
  case 5:
    ac = Algocat::ADVANCEDDS;
    break;
  case 6:
    ac = Algocat::GRAPH;
    break;
  }
}

void Visualizer::sorting_algo_list() {
  std::string algo_sort[] = {"Insertion Sort", "Selection Sort", "Merge Sort",
                             "Bubble Sort",    "Heap Sort",      "Quick Sort"};

  for (int i = 0; i < NUMBER_OF_SORT_ALGO; i++) {
    list_algo_sort[i].setFont(open_sans);
    list_algo_sort[i].setFillColor(sf::Color::White);
    list_algo_sort[i].setCharacterSize(10);
    list_algo_sort[i].setStyle(sf::Text::Bold);
    list_algo_sort[i].setPosition(50, 35 * i + 150);
    list_algo_sort[i].setString(algo_sort[i]);
  }
  list_algo_sort[NUMBER_OF_SORT_ALGO - 1].setFillColor(sf::Color::Red);
  list_algo_sort[0].setFillColor(sf::Color::Green);
}
