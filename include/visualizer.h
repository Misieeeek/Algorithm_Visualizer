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

public:
  enum class Algocat {
    SORTING,
    SEARCHING,
    DS,
    DYNAMIC,
    GREEDY,
    ADVANCEDDS,
    GRAPH
  };

  Visualizer(Screen **screen_ptr, Screen *menu);
  ~Visualizer();

  void draw(sf::RenderWindow &window) override;
  void move_up() override;
  void move_down() override;
  int pressed() override { return selected_algorithm; }
  void change_option(int selected) override;
  void handle_input() override;

  void drop_down(int option) override;
  void sorting_algo_list();
  void searching_algo_list();

private:
  Algocat ac;
};

#endif
