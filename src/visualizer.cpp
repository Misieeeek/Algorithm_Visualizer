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
    for (int i = 0; i < 2; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_SEARCH_ALGO; i++)
      window.draw(list_algo_search[i]);
    for (int i = 2; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 2: // DATA STRUCTURES
    for (int i = 0; i < 3; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_DS_ALGO; i++)
      window.draw(list_algo_ds[i]);
    for (int i = 3; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 3: // DYNAMIC Programming
    for (int i = 0; i < 4; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_DYNAMIC_ALGO; i++)
      window.draw(list_algo_dynamic[i]);
    for (int i = 4; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 4: // GREEDY ALGORITHMS
    for (int i = 0; i < 5; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_GREEDY_ALGO; i++)
      window.draw(list_algo_greedy[i]);
    for (int i = 5; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 5: // ADVANCED DATA STRUCTURES
    for (int i = 0; i < 6; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_ADVANCEDDS_ALGO; i++)
      window.draw(list_algo_advancedds[i]);
    for (int i = 6; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
    break;
  case 6: // GRAPH ALGORITHMS
    for (int i = 0; i < 7; i++)
      window.draw(list_algorithms[i]);
    for (int i = 0; i < NUMBER_OF_GRAPH_ALGO; i++)
      window.draw(list_algo_graph[i]);
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
    sorting_algo_list();
    break;
  case 1:
    ac = Algocat::SEARCHING;
    searching_algo_list();
    break;
  case 2:
    ac = Algocat::DS;
    ds_algo_list();
    break;
  case 3:
    ac = Algocat::DYNAMIC;
    dynamic_algo_list();
    break;
  case 4:
    ac = Algocat::GREEDY;
    greedy_algo_list();
    break;
  case 5:
    ac = Algocat::ADVANCEDDS;
    advancedds_algo_list();
    break;
  case 6:
    ac = Algocat::GRAPH;
    graph_algo_list();
    break;
  case 7:
    ac = Algocat::NONE;
    break;
  }
}

void Visualizer::sorting_algo_list() {
  std::string algo_sort[] = {"Insertion Sort", "Selection Sort", "Merge Sort",
                             "Bubble Sort",    "Heap Sort",      "Quick Sort"};

  for (int i = 0; i < NUMBER_OF_SORT_ALGO; i++) {
    list_algo_sort[i].setFont(open_sans);
    list_algo_sort[i].setFillColor(sf::Color::White);
    list_algo_sort[i].setCharacterSize(drop_down_item_font_size);
    list_algo_sort[i].setStyle(sf::Text::Bold);
    list_algo_sort[i].setPosition(100, 35 * i + 100);
    list_algo_sort[i].setString(algo_sort[i]);
  }

  list_algorithms[0].setPosition(50, 50);
  for (int i = 1; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setPosition(50, 50 * i + 260);
  }
}

void Visualizer::searching_algo_list() {
  std::string algo_search[] = {"Linear Search", "Binary Search"};

  for (int i = 0; i < NUMBER_OF_SEARCH_ALGO; i++) {
    list_algo_search[i].setFont(open_sans);
    list_algo_search[i].setFillColor(sf::Color::White);
    list_algo_search[i].setCharacterSize(drop_down_item_font_size);
    list_algo_search[i].setStyle(sf::Text::Bold);
    list_algo_search[i].setPosition(100, 35 * i + 250);
    list_algo_search[i].setString(algo_search[i]);
  }

  for (int i = 2; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setPosition(50, 50 * i + 220);
  }
}

void Visualizer::ds_algo_list() {
  std::string algo_ds[] = {"Stack",
                           "Queue",
                           "Linked List",
                           "Hash Table",
                           "Binary Search Tree",
                           "Red-Black Tree",
                           "AVL Tree",
                           "Treaps"};

  for (int i = 0; i < NUMBER_OF_DS_ALGO; i++) {
    list_algo_ds[i].setFont(open_sans);
    list_algo_ds[i].setFillColor(sf::Color::White);
    list_algo_ds[i].setCharacterSize(drop_down_item_font_size);
    list_algo_ds[i].setStyle(sf::Text::Bold);
    list_algo_ds[i].setPosition(100, 35 * i + 200);
    list_algo_ds[i].setString(algo_ds[i]);
  }

  for (int i = 0; i < 3; i++)
    list_algorithms[i].setPosition(50, 50 * i + 50);
  for (int i = 3; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setPosition(50, 50 * i + 320);
  }
}

void Visualizer::dynamic_algo_list() {
  std::string algo_dynamic[] = {"Cut Rod", "Cut Rod (Memoization)",
                                "Cut Rod (Tabulation)",
                                "Longest Common Subsequence"};

  for (int i = 0; i < NUMBER_OF_DYNAMIC_ALGO; i++) {
    list_algo_dynamic[i].setFont(open_sans);
    list_algo_dynamic[i].setFillColor(sf::Color::White);
    list_algo_dynamic[i].setCharacterSize(drop_down_item_font_size);
    list_algo_dynamic[i].setStyle(sf::Text::Bold);
    list_algo_dynamic[i].setPosition(100, 35 * i + 300);
    list_algo_dynamic[i].setString(algo_dynamic[i]);
  }

  for (int i = 0; i < 4; i++)
    list_algorithms[i].setPosition(50, 50 * i + 100);
  for (int i = 4; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setPosition(50, 50 * i + 230);
  }
}

void Visualizer::greedy_algo_list() {
  std::string algo_greedy[] = {"Huffman Coding", "Activity Selector"};

  for (int i = 0; i < NUMBER_OF_GREEDY_ALGO; i++) {
    list_algo_greedy[i].setFont(open_sans);
    list_algo_greedy[i].setFillColor(sf::Color::White);
    list_algo_greedy[i].setCharacterSize(drop_down_item_font_size);
    list_algo_greedy[i].setStyle(sf::Text::Bold);
    list_algo_greedy[i].setPosition(100, 35 * i + 390);
    list_algo_greedy[i].setString(algo_greedy[i]);
  }

  for (int i = 0; i < 5; i++)
    list_algorithms[i].setPosition(50, 50 * i + 140);
  for (int i = 5; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setPosition(50, 50 * i + 210);
  }
}

void Visualizer::advancedds_algo_list() {
  std::string algo_advancedds[] = {"B-Tree", "Fibonacci Heap",
                                   "Van Emde Boas Tree"};

  for (int i = 0; i < NUMBER_OF_ADVANCEDDS_ALGO; i++) {
    list_algo_advancedds[i].setFont(open_sans);
    list_algo_advancedds[i].setFillColor(sf::Color::White);
    list_algo_advancedds[i].setCharacterSize(drop_down_item_font_size);
    list_algo_advancedds[i].setStyle(sf::Text::Bold);
    list_algo_advancedds[i].setPosition(100, 35 * i + 400);
    list_algo_advancedds[i].setString(algo_advancedds[i]);
  }

  for (int i = 0; i < 6; i++)
    list_algorithms[i].setPosition(50, 50 * i + 100);
  for (int i = 6; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setPosition(50, 50 * i + 210);
  }
}

void Visualizer::graph_algo_list() {
  std::string algo_graph[] = {"1", "2", "3"};

  for (int i = 0; i < NUMBER_OF_GRAPH_ALGO; i++) {
    list_algo_graph[i].setFont(open_sans);
    list_algo_graph[i].setFillColor(sf::Color::White);
    list_algo_graph[i].setCharacterSize(drop_down_item_font_size);
    list_algo_graph[i].setStyle(sf::Text::Bold);
    list_algo_graph[i].setPosition(100, 35 * i + 445);
    list_algo_graph[i].setString(algo_graph[i]);
  }

  for (int i = 0; i < 7; i++)
    list_algorithms[i].setPosition(50, 50 * i + 100);
  for (int i = 7; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setPosition(50, 50 * i + 185);
  }
}
