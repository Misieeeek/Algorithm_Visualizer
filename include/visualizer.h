#ifndef VISUALIZER_H
#define VISUALIZER_H
#pragma once

#include "main_menu.h"
#include "main_window.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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

  // DROP DOWN MENU FOR SORTING ALGORITHMS
  sf::Text list_algo_sort[NUMBER_OF_SORT_ALGO];

  // DROP DOWN MENU FOR SEARCH ALGORITHMS
  sf::Text list_algo_search[NUMBER_OF_SEARCH_ALGO];

  // DROP DOWN MENU FOR DS ALGORITHMS
  sf::Text list_algo_ds[NUMBER_OF_DS_ALGO];

  // DROP DOWN MENU FOR DYNAMIC PROGRAMMING ALGORITHMS
  sf::Text list_algo_dynamic[NUMBER_OF_DYNAMIC_ALGO];

  // DROP DOWN MENU FOR GREEDY ALGORITHMS
  sf::Text list_algo_greedy[NUMBER_OF_GREEDY_ALGO];

  // DROP DOWN MENU FOR ADVANCED DATA STRUCTURES ALGORITHMS
  sf::Text list_algo_advancedds[NUMBER_OF_ADVANCEDDS_ALGO];

  // DROP DOWN MENU FOR GRAPH ALGORITHMS
  sf::Text list_algo_graph[NUMBER_OF_GRAPH_ALGO];

  // TEXT STYLES
  int category_font_size = 35;
  int drop_down_item_font_size = 20;

public:
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
  int pressed() override { return selected_algorithm; }
  void change_option(int selected) override;

  void drop_down(int option) override;
  void sorting_algo_list();
  void searching_algo_list();
  void ds_algo_list();
  void dynamic_algo_list();
  void greedy_algo_list();
  void advancedds_algo_list();
  void graph_algo_list();

private:
  Algocat ac;
};

#endif
