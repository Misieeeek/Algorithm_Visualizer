#ifndef VISUALIZER_H
#define VISUALIZER_H
#pragma once

#include "main_menu.h"
#include "main_window.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <vector>

#define NUMBER_OF_ALGORITHMS 8
#define NUMBER_OF_SORT_ALGO 6
#define NUMBER_OF_SEARCH_ALGO 2
#define NUMBER_OF_DS_ALGO 8
#define NUMBER_OF_DYNAMIC_ALGO 4
#define NUMBER_OF_GREEDY_ALGO 2
#define NUMBER_OF_ADVANCEDDS_ALGO 3
#define NUMBER_OF_GRAPH_ALGO 3

class Visualizer : public Screen {
private:
  // MAIN MENU FOR EVERY CATEGORY OF ALGORITHMS
  Screen **current_screen;
  Screen *main_menu;
  int selected_algorithm_index;
  sf::Text list_algorithms[NUMBER_OF_ALGORITHMS];
  sf::Font open_sans;
  int selected_algorithm;

  // DROP DOWN MENU ITEMS LIST
  std::vector<sf::Text> list_algo;

  // DROP DOWN MENU FOR SORTING ALGORITHMS
  sf::Text list_algo_sort[NUMBER_OF_SORT_ALGO];
  std::vector<std::string> algo_sort = {"Insertion Sort", "Selection Sort",
                                        "Merge Sort",     "Bubble Sort",
                                        "Heap Sort",      "Quick Sort"};

  // DROP DOWN MENU FOR SEARCH ALGORITHMS
  sf::Text list_algo_search[NUMBER_OF_SEARCH_ALGO];
  std::vector<std::string> algo_search = {"Linear Search", "Binary Search"};

  // DROP DOWN MENU FOR DS ALGORITHMS
  sf::Text list_algo_ds[NUMBER_OF_DS_ALGO];
  std::vector<std::string> algo_ds = {"Stack",
                                      "Queue",
                                      "Linked List",
                                      "Hash Table",
                                      "Binary Search Tree",
                                      "Red-Black Tree",
                                      "AVL Tree",
                                      "Treaps"};

  // DROP DOWN MENU FOR DYNAMIC PROGRAMMING ALGORITHMS
  sf::Text list_algo_dynamic[NUMBER_OF_DYNAMIC_ALGO];
  std::vector<std::string> algo_dynamic = {"Cut Rod", "Cut Rod (Memoization)",
                                           "Cut Rod (Tabulation)",
                                           "Longest Common Subsequence"};

  // DROP DOWN MENU FOR GREEDY ALGORITHMS
  sf::Text list_algo_greedy[NUMBER_OF_GREEDY_ALGO];
  std::vector<std::string> algo_greedy = {"Huffman Coding",
                                          "Activity Selector"};

  // DROP DOWN MENU FOR ADVANCED DATA STRUCTURES ALGORITHMS
  sf::Text list_algo_advancedds[NUMBER_OF_ADVANCEDDS_ALGO];
  std::vector<std::string> algo_advancedds = {"B-Tree", "Fibonacci Heap",
                                              "Van Emde Boas Tree"};

  // DROP DOWN MENU FOR GRAPH ALGORITHMS
  sf::Text list_algo_graph[NUMBER_OF_GRAPH_ALGO];
  std::vector<std::string> algo_graph = {"1", "2", "3"};

  // TEXT STYLES
  int category_font_size = 35;
  int drop_down_item_font_size = 20;

  // DROP DOWN MENU COUNTERS AND CHECKER FOR CATEGORY OPTION
  int dropped_items;
  int dropped_items_index;
  bool category_option;

  // CHOOSED OPTION FROM DROP DOWN MENU
  std::vector<std::vector<int>> algorithms;

public:
  // STATE OF PRESSED CATEGORY
  enum class Algocat {
    SORTING,
    SEARCHING,
    DS,
    DYNAMIC,
    GREEDY,
    ADVANCEDDS,
    GRAPH,
    NONE
  };

  Visualizer(Screen **screen_ptr, Screen *menu);
  ~Visualizer();

  void draw(sf::RenderWindow &window) override;
  void move_up() override;
  void move_down() override;
  int pressed() override;
  void change_option(int selected) override;

  void drop_down(int option) override;
  void general_algo_list(int number_of_categories,
                         std::vector<std::string> list_of_algo, int end_iter,
                         int add_val_pos_x_drop_down,
                         int add_val_pos_x_categories_before,
                         int adda_val_pos_x_categories_afer);
  void go_to_algo_screen(int selected);

private:
  Algocat ac;
};

#endif
