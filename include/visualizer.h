#ifndef VISUALIZER_H
#define VISUALIZER_H
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <array>
#include <charconv>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "main_menu.h"
#include "main_window.h"

// NUMBER OF ALGORITHMS BY CATEGORY
#define NUMBER_OF_ALGORITHMS 8
#define NUMBER_OF_SORT_ALGO 6
#define NUMBER_OF_SEARCH_ALGO 2
#define NUMBER_OF_DS_ALGO 8
#define NUMBER_OF_DYNAMIC_ALGO 4
#define NUMBER_OF_GREEDY_ALGO 2
#define NUMBER_OF_ADVANCEDDS_ALGO 3
#define NUMBER_OF_GRAPH_ALGO 3

// INPUT KEYS TO SKIP
#define DELETE_KEY 8
#define ENTER_KEY 13
#define MINUS_KEY 45

// NUMBER OF OPTIONS FOR SORTING ALGORITHMS
//#define NUMBER_OF_SORT_OPTIONS 3

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

// COMPARATOR FOR STD::PAIR<ALGOCAT, INT> TO BE USED IN THE MAP
struct algocat_pair_comparator {
  bool operator()(const std::pair<Algocat, int>& lhs,
                  const std::pair<Algocat, int>& rhs) const {
    if (lhs.first != rhs.first)
      return lhs.first < rhs.first;  // Compare categories first
    return lhs.second < rhs.second;  // Then compare the index
  }
};

// GLOBAL DECLARATION OF ALGORITHM MAP
extern std::map<std::pair<Algocat, int>, std::function<void()>,
                algocat_pair_comparator>
    algorithm_map;

// FORWARD DECLARATION OF CLASS Sorting_Class
class Sorting_Class;

class Visualizer : public Screen {
 public:
  Visualizer(Screen** screen_ptr, Screen* menu);
  ~Visualizer();

  // RESPOSIBLE FOR DRAWING EVERYTHING
  void draw(sf::RenderWindow& window) override;
  // MOVE UP/DOWN (OPTIONS)
  void move_up() override;
  void move_down() override;
  // RETURN A NUMBER OF WHICH OPTION WAS PRESSED
  int pressed() override;
  // RESPONSIBLE FOR CHANGING THE OPTION (WHEN SELECTED, DO SOMETHING)
  void change_option(int selected) override;
  // RESPOSIBLE FOR DROP DOWN MENUS OF EACH CATEGORY OF ALGORITHMS
  void drop_down(int option) override;
  // RESPONSIBLE FOR STYLE OF DROP DOWN MENU
  template <std::size_t N>
  void general_algo_list(std::size_t number_of_categories,
                         const std::array<std::string, N>& list_of_algo,
                         const int end_iter, const int add_val_pos_x_drop_down,
                         const int add_val_pos_x_categories_before,
                         const int adda_val_pos_x_categories_afer);
  // RESPONSIBLE FOR FINDING THE SELECTED ALGORITHM AND ACTIVATING IT FROM DOWN
  // MENU
  void go_to_algo_screen(int selected);
  // RESPONSIBLE FOR LOADING ALGORITHM SCREENS (BTW IT LOADS EVERYTHING WHEN
  // CONSTRUCTOR IS ACTIVATED, WOULD BE MUCH MORE EFFICIENT, WHEN IT LOADS ONE,
  // THE NEEDED ONE, AFTERWARDS IF NOT NEEDED ANYMORE DELETING IT).
  void initialize_algorithms();

 private:
  // KEEPS THE STATE OF ALGOCAT CURRENTLY SELECTED
  Algocat m_ac;

  // MAIN MENU FOR EVERY CATEGORY OF ALGORITHMS
  Screen** current_screen;
  Screen* main_menu;
  Sorting_Class* sort_class;
  int m_selected_algorithm_index;
  std::array<sf::Text, NUMBER_OF_ALGORITHMS> m_list_algorithms;
  int m_selected_algorithm;

  // DROP DOWN MENU ITEMS LIST
  std::vector<sf::Text> m_list_algo;

  // DROP DOWN MENU FOR SORTING ALGORITHMS
  std::array<sf::Text, NUMBER_OF_SORT_ALGO> m_list_algo_sort;
  std::array<std::string, NUMBER_OF_SORT_ALGO> m_algo_sort;

  // DROP DOWN MENU FOR SEARCH ALGORITHMS
  std::array<sf::Text, NUMBER_OF_SEARCH_ALGO> m_list_algo_search;
  std::array<std::string, NUMBER_OF_SEARCH_ALGO> m_algo_search;

  // DROP DOWN MENU FOR DS ALGORITHMS
  std::array<sf::Text, NUMBER_OF_DS_ALGO> m_list_algo_ds;
  std::array<std::string, NUMBER_OF_DS_ALGO> m_algo_ds;

  // DROP DOWN MENU FOR DYNAMIC PROGRAMMING ALGORITHMS
  std::array<sf::Text, NUMBER_OF_DYNAMIC_ALGO> m_list_algo_dynamic;
  std::array<std::string, NUMBER_OF_DYNAMIC_ALGO> m_algo_dynamic;

  // DROP DOWN MENU FOR GREEDY ALGORITHMS
  std::array<sf::Text, NUMBER_OF_GREEDY_ALGO> m_list_algo_greedy;
  std::array<std::string, NUMBER_OF_GREEDY_ALGO> m_algo_greedy;

  // DROP DOWN MENU FOR ADVANCED DATA STRUCTURES ALGORITHMS
  std::array<sf::Text, NUMBER_OF_ADVANCEDDS_ALGO> m_list_algo_advancedds;
  std::array<std::string, NUMBER_OF_ADVANCEDDS_ALGO> m_algo_advancedds;

  // DROP DOWN MENU FOR GRAPH ALGORITHMS
  std::array<sf::Text, NUMBER_OF_GRAPH_ALGO> m_list_algo_graph;
  std::array<std::string, NUMBER_OF_GRAPH_ALGO> m_algo_graph;

  // TEXT STYLES
  int m_category_font_size;
  int m_drop_down_item_font_size;

  // DROP DOWN MENU COUNTERS AND CHECKER FOR CATEGORY OPTION
  int m_dropped_items;
  int m_dropped_items_index;
  bool m_category_option;
};

class Sorting_Class : public Screen {
 public:
  // IHERITENCE FROM CLASS SCREEN
  void draw(sf::RenderWindow& window) override;
  void move_up() override;
  void move_down() override;
  void move_left() override;
  void move_right() override;
  int pressed() override;
  void change_option(int selected) override;
  void drop_down(int option) override;
  void typed_on(sf::Event input) override;

  Sorting_Class(Screen** screen_ptr,
                Visualizer* viz_ptr);  // MENU HAS TO CHANGE
                                       // TO VISUALIZER
  ~Sorting_Class();

  void set_style(std::vector<std::string> variants, int y_pos);
  void insertion_sort();
  void textbox(int char_size_textbox, int number_of_inputs, int pos_y);

  // RESPONSIBLE FOR CHANDELING INPUTBOX
  void input_box_selected(int item);

  // SET STYLE FOR VISUALIZATION BUTTONS
  void visualization_buttons_style(int pos_x);

  // GET/SET M_SIZES
  void set_m_sizes(size_t options, size_t variants, size_t buttons, size_t sum);

 private:
  // DISPLAYS SCREEN FOR SORTING
  Screen** current_screen;
  Visualizer* visualize;
  int m_selected_sorting_algo_index;
  int m_selected_sort_algo;

  // LIST OF ALGORITHMS VARIANTS, VARIES BY SORTING ALGORITHM
  std::vector<sf::Text> m_algorithm_variants;

  // TEXT STYLE
  // TODO - C++20 CHANGE TO std::span
  int m_char_size_text_variants;
  std::array<std::string, 3> m_headers_text;
  std::array<sf::Text, 3> m_headers;

  // VISUALIZATION OPTIONS
  // THIS VECTOR KEEPS STATE OF:
  // NUMBER OF ELEMENTS, MINIMUM RANGE OF NUMBERS, MAXIMUM RANGE OF NUMBERS
  std::array<int, 3> m_visualization_options;
  std::array<std::string, 3> m_visualization_options_names;

  // VISUALIZATION BUTTONS
  std::array<std::string, 4> m_visualization_buttons_names;
  std::array<sf::Text, 4> m_visualization_buttons_text;
  std::array<sf::RectangleShape, 4> m_visualization_buttons_shape;

  // INPUT FOR OPTIONS
  std::array<sf::Text, 3> m_textbox_input_style;
  std::ostringstream m_text_input;
  int m_selected_input_option;
  std::string m_temp_value;

  // IF THE IMPUT OPTION IS SELECTED
  bool m_possible_input;

  // ARRAY OF SIZES (VIZ OPTIONS, ALGO VARIANTS, VIZ BUTTONS, SUM OF THEM)
  std::array<size_t, 4> m_sizes;

  // INPUT LOGIC
  void input_logic(int char_typed) {
    if (char_typed != DELETE_KEY && char_typed != ENTER_KEY) {
      if (m_temp_value != "" && char_typed == MINUS_KEY)
        std::cerr << "Don't use minus sign between numbers" << std::endl;
      else {
        if (m_temp_value.length() >= 7)
          std::cerr << "Value is too big/small" << std::endl;
        else {
          m_text_input << static_cast<char>(char_typed);
          m_temp_value.push_back(static_cast<char>(char_typed));
          m_textbox_input_style[m_selected_input_option].setString(
              m_text_input.str() + "_");
        }
      }
    } else if (char_typed == DELETE_KEY) {
      if (m_text_input.str().length() > 0)
        delete_last_char();
    }
  }

  // DELETE INPUT
  void delete_last_char() {
    std::string t = m_text_input.str();
    std::string newT = "";
    for (int i = 0; i < t.length() - 1; i++) {
      newT += t[i];
    }
    m_text_input.str("");
    m_text_input << newT;
    m_textbox_input_style[m_selected_input_option].setString(
        m_text_input.str());
    m_temp_value.pop_back();
  }
};

#endif
