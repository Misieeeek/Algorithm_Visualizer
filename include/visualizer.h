#ifndef VISUALIZER_H
#define VISUALIZER_H
#pragma once

#include "main_menu.h"
#include "main_window.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define NUMBER_OF_ALGORITHMS 8
#define NUMBER_OF_SORT_ALGO 6

class Visualizer : public Screen {
private:
  // MAIN MENU FOR EVERY CATEGORY OF ALGORITHMS
  Screen **current_screen;
  MainMenu *main_menu;
  int selected_algorithm_index;
  sf::Text list_algorithms[NUMBER_OF_ALGORITHMS];
  sf::Font open_sans;
  int selected_algorithm;
  bool opend;

  // DROP DOWN MENU FOR SORTING ALGORITHMS
  sf::Text list_algo_sort[NUMBER_OF_SORT_ALGO];

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

  Visualizer(Screen **screen_ptr, MainMenu *menu);
  ~Visualizer();

  void draw(sf::RenderWindow &window) override;
  void move_up() override;
  void move_down() override;
  int pressed() override { return selected_algorithm; }
  void change_option(int selected) override;
  void set_state(State new_state) override;

  void drop_down(int option) override;
  void sorting_algo_list();

private:
  Algocat ac;
};

#endif
