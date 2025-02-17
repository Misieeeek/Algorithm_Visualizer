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
    list_algorithms[i].setCharacterSize(category_font_size);
    list_algorithms[i].setStyle(sf::Text::Bold);
    list_algorithms[i].setPosition(50, 50 * i + 150);
    list_algorithms[i].setString(algo[i]);
  }
  list_algorithms[NUMBER_OF_ALGORITHMS - 1].setFillColor(sf::Color::Red);
  list_algorithms[0].setFillColor(sf::Color::Green);
  selected_algorithm = 0;
  dropped = false;
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
  switch (static_cast<int>(ac)) {
  case 0: // SORTING
    window.draw(list_algorithms[0]);
    for (int i = 0; i < NUMBER_OF_SORT_ALGO; i++)
      window.draw(list_algo[i]);
    for (int i = 1; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 1: // SEARCHING
    for (int i = 0; i < 2; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_SEARCH_ALGO; i++)
      window.draw(list_algo[i]);
    for (int i = 2; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 2: // DATA STRUCTURES
    for (int i = 0; i < 3; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_DS_ALGO; i++)
      window.draw(list_algo[i]);
    for (int i = 3; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 3: // DYNAMIC Programming
    for (int i = 0; i < 4; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_DYNAMIC_ALGO; i++)
      window.draw(list_algo[i]);
    for (int i = 4; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 4: // GREEDY ALGORITHMS
    for (int i = 0; i < 5; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_GREEDY_ALGO; i++)
      window.draw(list_algo[i]);
    for (int i = 5; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 5: // ADVANCED DATA STRUCTURES
    for (int i = 0; i < 6; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_ADVANCEDDS_ALGO; i++)
      window.draw(list_algo[i]);
    for (int i = 6; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 6: // GRAPH ALGORITHMS
    for (int i = 0; i < 7; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_GRAPH_ALGO; i++)
      window.draw(list_algo[i]);
    for (int i = 7; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 7:
    for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++) {
      list_algorithms[i].setPosition(50, 50 * i + 150);
      window.draw(list_algorithms[i]);
    }
    break;
  default:
    for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++) {
      list_algorithms[i].setPosition(50, 50 * i + 150);
      window.draw(list_algorithms[i]);
    }
    break;
  }
}

void Visualizer::change_option(int selected) {
  switch (selected) {
  case 0: // SORTING
    if (opend) {
      if (!dropped) {
        dropped = true;
        drop_down(selected);
      } else {
        drop_down(7);
        dropped = false;
      }
    }
    break;
  case 1: // SEARCHING
    if (!dropped) {
      dropped = true;
      drop_down(selected);
    } else {
      drop_down(7);
      dropped = false;
    }
    break;
  case 2: // DS
    if (!dropped) {
      dropped = true;
      drop_down(selected);
    } else {
      drop_down(7);
      dropped = false;
    }
    break;
  case 3: // DYNAMIC ALGORITHMS
    if (!dropped) {
      dropped = true;
      drop_down(selected);
    } else {
      dropped = false;
      drop_down(7);
    }
    break;
  case 4: // GREEDY ALGORITHMS
    if (!dropped) {
      dropped = true;
      drop_down(selected);
    } else {
      dropped = false;
      drop_down(7);
    }
    break;
  case 5: // ADVANCED  DS
    if (!dropped) {
      dropped = true;
      drop_down(selected);
    } else {
      dropped = false;
      drop_down(7);
    }
    break;
  case 6: // GRAPH ALGORITHMS
    if (!dropped) {
      dropped = true;
      drop_down(selected);
    } else {
      dropped = false;
      drop_down(7);
    }
    break;
  case 7: // EXIT
    opend = false;
    selected_algorithm = 0;
    selected_algorithm_index = 0;
    list_algorithms[0].setFillColor(sf::Color::Green);
    list_algorithms[NUMBER_OF_ALGORITHMS - 1].setFillColor(sf::Color::Red);
    dropped = true;
    *current_screen = main_menu;
    break;
  }
}

void Visualizer::drop_down(int option) {
  switch (option) {
  case 0:
    ac = Algocat::SORTING;
    general_algo_list(NUMBER_OF_SORT_ALGO, algo_sort, 1, 100, 50, 260);
    // sorting_algo_list();
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
