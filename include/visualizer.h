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
#include <span>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "main_menu.h"
#include "main_window.h"

// FORWARD DECLARATION OF CLASS Sorting_Class and Visualization
class Sorting_Class;
class Visualization;

class Visualizer : public Screen {
 public:
  Visualizer(Screen** screen_ptr, Screen* menu);
  virtual ~Visualizer();

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
  void general_algo_list(std::size_t number_of_categories,
                         std::span<std::string> list_of_algo, int end_iter,
                         int add_val_pos_x_drop_down,
                         int add_val_pos_x_categories_before,
                         int adda_val_pos_x_categories_afer);
  // RESPONSIBLE FOR FINDING THE SELECTED ALGORITHM AND ACTIVATING IT FROM DOWN
  // MENU
  void go_to_algo_screen(int selected);

  // RESPONSIBLE FOR LOADING ALGORITHM SCREENS
  void initialize_algorithms();

  // STATE OF PRESSED CATEGORY
  enum class algo_cat {
    sorting,
    searching,
    ds,
    dynamic,
    greedy,
    advancedds,
    graph,
    none
  };

  // COMPARATOR FOR STD::PAIR<ALGOCAT, INT> TO BE USED IN THE MAP
  struct algocat_pair_comparator {
    bool operator()(const std::pair<algo_cat, int>& lhs,
                    const std::pair<algo_cat, int>& rhs) const {
      if (lhs.first != rhs.first)
        return lhs.first < rhs.first;  // Compare categories first
      return lhs.second < rhs.second;  // Then compare the index
    }
  };

 private:
  // KEEPS THE STATE OF ALGOCAT CURRENTLY SELECTED
  algo_cat m_ac;

  // MAIN MENU FOR EVERY CATEGORY OF ALGORITHMS
  Screen** current_screen;
  Screen* main_menu;
  Sorting_Class* sort_class;
  int m_selected_algorithm_index;
  static constexpr std::size_t c_num_algos = 8;
  std::array<sf::Text, c_num_algos> m_list_algorithms;
  int m_selected_algorithm;

  // DROP DOWN MENU ITEMS LIST
  std::vector<sf::Text> m_list_algo;

  // CONSTANTS FOR NUMBER OF ALGORITHMS IN DIFFERENT CATEGORIES
  static constexpr std::size_t c_num_sort = 6;
  static constexpr std::size_t c_num_search = 2;
  static constexpr std::size_t c_num_ds = 8;
  static constexpr std::size_t c_num_dynamic = 4;
  static constexpr std::size_t c_num_greedy = 2;
  static constexpr std::size_t c_num_advancedds = 3;
  static constexpr std::size_t c_num_graph = 3;

  // DROP DOWN MENU FOR SORTING ALGORITHMS
  std::array<sf::Text, c_num_sort> m_list_algo_sort;
  std::array<std::string, c_num_sort> m_algo_sort;

  // DROP DOWN MENU FOR SEARCH ALGORITHMS
  std::array<sf::Text, c_num_search> m_list_algo_search;
  std::array<std::string, c_num_search> m_algo_search;

  // DROP DOWN MENU FOR DS ALGORITHMS
  std::array<sf::Text, c_num_ds> m_list_algo_ds;
  std::array<std::string, c_num_ds> m_algo_ds;

  // DROP DOWN MENU FOR DYNAMIC PROGRAMMING ALGORITHMS
  std::array<sf::Text, c_num_dynamic> m_list_algo_dynamic;
  std::array<std::string, c_num_dynamic> m_algo_dynamic;

  // DROP DOWN MENU FOR GREEDY ALGORITHMS
  std::array<sf::Text, c_num_greedy> m_list_algo_greedy;
  std::array<std::string, c_num_greedy> m_algo_greedy;

  // DROP DOWN MENU FOR ADVANCED DATA STRUCTURES ALGORITHMS
  std::array<sf::Text, c_num_advancedds> m_list_algo_advancedds;
  std::array<std::string, c_num_advancedds> m_algo_advancedds;

  // DROP DOWN MENU FOR GRAPH ALGORITHMS
  std::array<sf::Text, c_num_graph> m_list_algo_graph;
  std::array<std::string, c_num_graph> m_algo_graph;

  // TEXT STYLES
  const int m_category_font_size;
  const int m_drop_down_item_font_size;

  // DROP DOWN MENU COUNTERS AND CHECKER FOR CATEGORY OPTION
  int m_dropped_items;
  int m_dropped_items_index;
  bool m_category_option;

  // INITIALIZE ALGORITHM MAP, DIVIDED PER CATEGORY
  void initialize_sorting();
  void initialize_searching();
  void initialize_ds();
  void initialize_dynamic();
  void initialize_greedy();
  void initialize_advancedds();
  void initialize_graph();

  // ALGORITHM MAP(CATEGORY, INDEX)
  std::map<std::pair<algo_cat, int>, std::function<void()>,
           algocat_pair_comparator>
      algorithm_map;

  //void generate_visualization() {};
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
  virtual ~Sorting_Class();

  void set_style(std::vector<std::string> variants, int y_pos);
  void insertion_sort();
  void textbox(int char_size_textbox, std::size_t number_of_inputs, int pos_y);

  // RESPONSIBLE FOR CHANDELING INPUTBOX
  void input_box_selected(int item);

  // SET STYLE FOR VISUALIZATION BUTTONS
  void visualization_buttons_style(int pos_x);

  //
  void algo_viz();
  void algo_viz(std::size_t n_elements, int min_val, int max_val);
  // OVERLOAD algo_viz() FUNCTION, ADDITIONAL PARAMETER case, WHERE false = WORST CASE
  void algo_viz(std::size_t n_elements, int min_val, int max_val, bool bw_case);

 private:
  // DISPLAYS SCREEN FOR SORTING
  Screen** current_screen;
  Visualizer* visualize;
  Visualization* final_visual;
  int m_selected_sorting_algo_index;
  int m_selected_sort_algo;
  int m_choosed_algo;
  // CONSTANTS
  // LISTED IMPORTANT KEYS
  static constexpr int c_delete_key = 8;
  static constexpr int c_enter_key = 13;
  static constexpr int c_minus_key = 45;
  // HOLDING THE SIZE OF CERTAIN ELEMENTS
  static constexpr int c_headers = 3;
  static constexpr int c_options = 3;
  static constexpr int c_buttons = 4;

  // LIST OF ALGORITHMS VARIANTS, VARIES BY SORTING ALGORITHM
  std::vector<sf::Text> m_algorithm_variants;
  std::size_t m_variants_size;

  // TEXT STYLE
  int m_char_size_text_variants;
  std::array<std::string, c_headers> m_headers_text;
  std::array<sf::Text, c_headers> m_headers;

  // VISUALIZATION OPTIONS
  // THIS VECTOR KEEPS STATE OF:
  // NUMBER OF ELEMENTS, MINIMUM RANGE OF NUMBERS, MAXIMUM RANGE OF NUMBERS
  std::array<int, c_options> m_visualization_options;
  std::array<std::string, c_options> m_visualization_options_names;

  // VISUALIZATION BUTTONS
  std::array<std::string, c_buttons> m_visualization_buttons_names;
  std::array<sf::Text, c_buttons> m_visualization_buttons_text;
  std::array<sf::RectangleShape, c_buttons> m_visualization_buttons_shape;

  // INPUT FOR OPTIONS
  std::array<sf::Text, c_options> m_textbox_input_style;
  std::ostringstream m_text_input;
  int m_selected_input_option;
  std::string m_temp_value;

  // IF THE IMPUT OPTION IS SELECTED
  bool m_possible_input;

  // INPUT LOGIC
  void input_logic(int char_typed) {
    if (char_typed != c_delete_key && char_typed != c_enter_key) {
      if (m_temp_value != "" && char_typed == c_minus_key)
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
    } else if (char_typed == c_delete_key) {
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

class Visualization : public Screen {
 public:
  Visualization(Screen** screen_ptr, Sorting_Class* sort_class_ptr);
  ~Visualization();

  void draw(sf::RenderWindow& window) override;
  void move_left() override;
  void move_right() override;
  int pressed() override;
  void change_option(int selected) override;

  void visual();

  // SET STYLES FOR SCREEN
  void set_styles();

  // SET PREVIOUSLY CHOOSED OPTIONS
  void set_options(std::size_t n_elements, int min_val, int max_val);

 private:
  // DISPLAYS SCREEN FOR SORTING
  Screen** current_screen;
  Sorting_Class* sort_class;
  int m_selected_button_index;
  int m_selected_button;

  // CONSTANTS
  static constexpr std::size_t c_buttons = 2;
  static constexpr std::size_t c_info = 1;
  static constexpr std::size_t c_options = 3;

  // BUTTONS SHAPE, TEXT, NAMES
  std::array<sf::Text, c_buttons> m_buttons_text;
  std::array<std::string, c_buttons> m_buttons_names;
  std::array<sf::RectangleShape, c_buttons> m_buttons_shape;

  // INFORMATION ABOUT VISUALIZATION
  std::array<sf::Text, c_info> m_info_text;

  // STATE OF VISUALIZING (FALSE - NOT VISUALIZING, TRUE - VISUALIZING RIGHT NOW)
  bool m_visualizaing;

  // NUMBER OF ELEMENTS, MINIMUM RANGE OF NUMBERS, MAXIMUM RANGE OF NUMBERS
  std::array<int, c_options> m_options;
};

#endif
