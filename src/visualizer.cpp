#include "visualizer.h"
#include "main_menu.h"
#include "main_window.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>

Visualizer::Visualizer(Screen **screen_ptr, Screen *menu)
    : selected_algorithm_index(0) {

  std::filesystem::current_path(
      std::filesystem::path(__FILE__).parent_path().parent_path());

  if (!open_sans.loadFromFile("assets/fonts/OpenSans-Regular.ttf")) {
    std::cerr << "Failed to load font" << std::endl;
  }

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
  opend = true;
  // main_active = false;
  switch (static_cast<int>(ac)) {
  case 0: // SORTING
    window.draw(list_algorithms[0]);
    for (int i = 0; i < NUMBER_OF_SORT_ALGO; i++)
      window.draw(list_algo_sort[i]);
    for (int i = 1; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 1: // SEARCHING
    for (int i = 0; i < 1; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_SEARCH_ALGO; i++)
      window.draw(list_algo_search[i]);
    for (int i = 2; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
  default:
    for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++) {
      list_algorithms[i].setPosition(50, 50 * i + 150);
      window.draw(list_algorithms[i]);
    }
  }
}

void Visualizer::change_option(int selected) {
  switch (selected) {
  case 0: // SORTING
    if (opend)
      drop_down(selected);
    break;
  case 1: // SEARCHING
    drop_down(selected);
    break;
  case 2: // DS
    drop_down(selected);
    break;
  case 3: // DYNAMIC ALGORITHMS
    drop_down(selected);
    break;
  case 4: // GREEDY ALGORITHMS
    drop_down(selected);
    break;
  case 5: // ADVANCED  DS
    drop_down(selected);
    break;
  case 6: // GRAPH ALGORITHMS
    drop_down(selected);
    break;
  case 7: // EXIT
    opend = false;
    selected_algorithm = 0;
    selected_algorithm_index = 0;
    list_algorithms[0].setFillColor(sf::Color::Green);
    list_algorithms[NUMBER_OF_ALGORITHMS - 1].setFillColor(sf::Color::Red);
    // main_active = true;
    *current_screen = main_menu;
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
    searching_algo_list();
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
    list_algo_sort[i].setCharacterSize(20);
    list_algo_sort[i].setStyle(sf::Text::Bold);
    list_algo_sort[i].setPosition(100, 35 * i + 200);
    list_algo_sort[i].setString(algo_sort[i]);
  }
  list_algo_sort[NUMBER_OF_SORT_ALGO - 1].setFillColor(sf::Color::Red);
  list_algo_sort[0].setFillColor(sf::Color::Green);

  for (int i = 1; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setPosition(50, 35 * i + 360);
  }
}

void Visualizer::searching_algo_list() {
  std::string algo_search[] = {"Linear Search", "Binary Search"};

  for (int i = 0; i < NUMBER_OF_SEARCH_ALGO; i++) {
    list_algo_search[i].setFont(open_sans);
    list_algo_search[i].setFillColor(sf::Color::White);
    list_algo_search[i].setCharacterSize(20);
    list_algo_search[i].setStyle(sf::Text::Bold);
    list_algo_search[i].setPosition(100, 35 * i + 250);
    list_algo_search[i].setString(algo_search[i]);
  }
  list_algo_search[NUMBER_OF_SEARCH_ALGO - 1].setFillColor(sf::Color::Red);
  list_algo_search[0].setFillColor(sf::Color::Green);

  for (int i = 2; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setPosition(0, 35 * i + 360);
  }
}

void Visualizer::handle_input() {}
