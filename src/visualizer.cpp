#include "visualizer.h"
#include "main_menu.h"
#include "main_window.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>

Visualizer::Visualizer(Screen **screen_ptr, Screen *menu)
    : selected_algorithm_index(0), selected_algorithm(0),
      category_option(true) {

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
    list_algorithms[i].setCharacterSize(category_font_size);
    list_algorithms[i].setStyle(sf::Text::Bold);
    list_algorithms[i].setPosition(50, 50 * i + 150);
    list_algorithms[i].setString(algo[i]);
  }
  list_algorithms[NUMBER_OF_ALGORITHMS - 1].setFillColor(sf::Color::Red);
  list_algorithms[0].setFillColor(sf::Color::Green);
  dropped = false;

  for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++) {
    for (int j = 0; i <)
  }
}

Visualizer::~Visualizer() {}

void Visualizer::move_up() {
  if (dropped || !category_option) {
    if (dropped_items_index - 1 >= 0) {
      list_algo[dropped_items_index].setFillColor(sf::Color::White);
      dropped_items_index--;
      list_algo[dropped_items_index].setFillColor(sf::Color::Green);
      dropped_items = dropped_items_index;
    } else {
      category_option = true;
      list_algo[dropped_items_index].setFillColor(sf::Color::White);
      list_algorithms[selected_algorithm_index].setFillColor(sf::Color::Green);
    }
  } else {
    if (selected_algorithm_index - 1 >= 0) {
      if (selected_algorithm_index == NUMBER_OF_ALGORITHMS - 1)
        list_algorithms[selected_algorithm_index].setFillColor(sf::Color::Red);
      else
        list_algorithms[selected_algorithm_index].setFillColor(
            sf::Color::White);
      selected_algorithm_index--;
      list_algorithms[selected_algorithm_index].setFillColor(sf::Color::Green);
      selected_algorithm = selected_algorithm_index;
    }
  }
}

void Visualizer::move_down() {
  if (dropped) {
    if (dropped_items_index + 1 < list_algo.size()) {
      if (category_option) {
        category_option = false;
        list_algo[0].setFillColor(sf::Color::Green);
        list_algorithms[selected_algorithm_index].setFillColor(
            sf::Color::White);
      } else {
        list_algo[dropped_items_index].setFillColor(sf::Color::White);
        dropped_items_index++;
        list_algo[dropped_items_index].setFillColor(sf::Color::Green);
        dropped_items = dropped_items_index;
      }
    }
  } else {
    if (selected_algorithm_index + 1 < NUMBER_OF_ALGORITHMS) {
      list_algorithms[selected_algorithm_index].setFillColor(sf::Color::White);
      selected_algorithm_index++;
      list_algorithms[selected_algorithm_index].setFillColor(sf::Color::Green);
      selected_algorithm = selected_algorithm_index;
    }
  }
}

void Visualizer::draw(sf::RenderWindow &window) {
  opend = true;
  if (static_cast<int>(ac) >= 0 && static_cast<int>(ac) < 7) {
    for (int i = 0; i < list_algo.size(); i++)
      window.draw(list_algo[i]);
    for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
  } else {
    for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++) {
      list_algorithms[i].setPosition(50, 50 * i + 150);
      window.draw(list_algorithms[i]);
    }
  }
}

void Visualizer::change_option(int selected) {
  if (!dropped) {        // Place where drop down menu is deactivated
    if (selected == 7) { // EXIT out of visualizer
      opend = false;
      selected_algorithm = 0;
      selected_algorithm_index = 0;
      list_algorithms[0].setFillColor(sf::Color::Green);
      list_algorithms[NUMBER_OF_ALGORITHMS - 1].setFillColor(sf::Color::Red);
      dropped = true;
      *current_screen = main_menu;
    } else {       // Every other option than EXIT
      if (opend) { // Prevents activating drop down menu comming from main menu
        dropped = true;
        dropped_items = 0;
        dropped_items_index = 0;
        drop_down(selected);
      } else {
        drop_down(7);
        dropped = false;
      }
    }
  } else {                 // Place where drop down menu is active
    if (category_option) { // currently standing at algorithm category
      dropped = false;
      drop_down(7);
    } else { // Place where drop down menus options are executed
      go_to_algo_screen(selected);
    }
  }
}

void Visualizer::drop_down(int option) {
  switch (option) {
  case 0:
    ac = Algocat::SORTING;
    general_algo_list(NUMBER_OF_SORT_ALGO, algo_sort, 1, 100, 50, 260);
    break;
  case 1:
    ac = Algocat::SEARCHING;
    general_algo_list(NUMBER_OF_SEARCH_ALGO, algo_search, 2, 250, 150, 220);
    break;
  case 2:
    ac = Algocat::DS;
    general_algo_list(NUMBER_OF_DS_ALGO, algo_ds, 3, 200, 50, 320);
    break;
  case 3:
    ac = Algocat::DYNAMIC;
    general_algo_list(NUMBER_OF_DYNAMIC_ALGO, algo_dynamic, 4, 300, 100, 230);
    break;
  case 4:
    ac = Algocat::GREEDY;
    general_algo_list(NUMBER_OF_GREEDY_ALGO, algo_greedy, 5, 390, 140, 210);
    break;
  case 5:
    ac = Algocat::ADVANCEDDS;
    general_algo_list(NUMBER_OF_ADVANCEDDS_ALGO, algo_advancedds, 6, 400, 100,
                      210);
    break;
  case 6:
    ac = Algocat::GRAPH;
    general_algo_list(NUMBER_OF_GRAPH_ALGO, algo_graph, 7, 445, 100, 185);
    break;
  case 7:
    ac = Algocat::NONE;
    break;
  }
}

void Visualizer::general_algo_list(int number_of_categories,
                                   std::vector<std::string> list_of_algo,
                                   int end_iter, int add_val_pos_x_drop_down,
                                   int add_val_pos_x_categories_before,
                                   int add_val_pos_x_categories_after) {
  list_algo.resize(number_of_categories);
  for (int i = 0; i < number_of_categories; i++) {
    list_algo[i].setFont(open_sans);
    list_algo[i].setFillColor(sf::Color::White);
    list_algo[i].setCharacterSize(drop_down_item_font_size);
    list_algo[i].setStyle(sf::Text::Bold);
    list_algo[i].setPosition(100, 35 * i + add_val_pos_x_drop_down);
    list_algo[i].setString(list_of_algo[i]);
  }

  for (int i = 0; i < end_iter; i++)
    list_algorithms[i].setPosition(50,
                                   50 * i + add_val_pos_x_categories_before);
  for (int i = end_iter; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setPosition(50, 50 * i + add_val_pos_x_categories_after);
  }
}

int Visualizer::pressed() {
  if (category_option)
    return selected_algorithm;
  else
    return dropped_items;
}

void Visualizer::go_to_algo_screen(int selected) {}
