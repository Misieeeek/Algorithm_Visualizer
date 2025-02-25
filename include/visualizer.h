#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <algorithm>
#include <iostream>
#include <sstream>
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <charconv>
#include <functional>
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
  // MOVE UP/DOWN/RIGHT/LEFT (OPTIONS)
  void move_up() override;
  void move_down() override;
  void move_left() override;
  void move_right() override;
  // RETURN A NUMBER OF WHICH OPTION WAS PRESSED
  int pressed() override;
  // RESPONSIBLE FOR CHANGING THE OPTION (WHEN SELECTED, DO SOMETHING)
  void change_option(int selected) override;
  // RESPOSIBLE FOR DROP DOWN MENUS OF EACH CATEGORY OF ALGORITHMS
  void drop_down(int option) override;
  // RESPONSIBLE FOR STYLE OF DROP DOWN MENU
  void general_algo_list(int number_of_categories,
                         std::vector<std::string> list_of_algo, int end_iter,
                         int add_val_pos_x_drop_down,
                         int add_val_pos_x_categories_before,
                         int adda_val_pos_x_categories_afer);
  // RESPONSIBLE FOR FINDING THE SELECTED ALGORITHM AND ACTIVATING IT FROM DOWN
  // MENU
  void go_to_algo_screen(int selected);
  //
  void render();
  // RESPONSIBLE FOR LOADING ALGORITHM SCREENS (BTW IT LOADS EVERYTHING WHEN
  // CONSTRUCTOR IS ACTIVATED, WOULD BE MUCH MORE EFFICIENT, WHEN IT LOADS ONE,
  // THE NEEDED ONE, AFTERWARDS IF NOT NEEDED ANYMORE DELETING IT).
  void initialize_algorithms();

  void typed_on(sf::Event input) override;

 private:
  // KEEPS THE STATE OF ALGOCAT CURRENTLY SELECTED
  Algocat ac;

  // MAIN MENU FOR EVERY CATEGORY OF ALGORITHMS
  Screen** current_screen;
  Screen* main_menu;
  Sorting_Class* sort_class;
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

 private:
  // DISPLAYS SCREEN FOR SORTING
  Screen** current_screen;
  Visualizer* visualize;
  int selected_sorting_algo_index;
  sf::Font open_sans;
  int selected_sort_algo;

  // LIST OF ALGORITHMS VARIANTS, VARIES BY SORTING ALGORITHM
  std::vector<sf::Text> algorithm_variants;

  // TEXT STYLE
  int char_size_text_variants;
  std::vector<std::string> headers_text;
  std::vector<sf::Text> headers;

  // VISUALIZATION OPTIONS
  // THIS VECTOR KEEPS STATE OF: NUMBER OF ELEMENTS, MINIMUM RANGE OF NUMBERS, MAXIMUM RANGE OF NUMBERS
  std::vector<int> visualization_options;
  std::vector<std::string> visualization_options_names;

  // VISUALIZATION BUTTONS
  std::vector<std::string> visualization_buttons_names;
  std::vector<sf::Text> visualization_buttons;

  // INPUT FOR OPTIONS
  std::vector<sf::Text> textbox_input_style;
  std::ostringstream text_input;
  int selected_input_option;
  std::string temp_value;

  // IF THE IMPUT OPTION IS SELECTED
  bool possible_input;

  // INPUT LOGIC
  void input_logic(int char_typed) {
    if (char_typed != DELETE_KEY && char_typed != ENTER_KEY) {
      if (temp_value != "" && char_typed == MINUS_KEY)
        std::cerr << "Don't use minus sign between numbers" << std::endl;
      else {
        if (temp_value.length() >= 7)
          std::cerr << "Value is too big/small" << std::endl;
        else {
          text_input << static_cast<char>(char_typed);
          temp_value.push_back(static_cast<char>(char_typed));
          textbox_input_style[selected_input_option].setString(
              text_input.str() + "_");
        }
      }
    } else if (char_typed == DELETE_KEY) {
      if (text_input.str().length() > 0)
        delete_last_char();
    }
  }

  // DELETE INPUT
  void delete_last_char() {
    std::string t = text_input.str();
    std::string newT = "";
    for (int i = 0; i < t.length() - 1; i++) {
      newT += t[i];
    }
    text_input.str("");
    text_input << newT;
    textbox_input_style[selected_input_option].setString(text_input.str());
    temp_value.pop_back();
  }
};

#endif
