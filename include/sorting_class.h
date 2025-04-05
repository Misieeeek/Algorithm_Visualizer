#ifndef SORTCLASS_H
#define SORTCLASS_H
#pragma once

#include "visualizer.h"

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
  void typed_on(sf::Event input) override;

  Sorting_Class(Screen** screen_ptr, Visualizer* viz_ptr,
                sf::RenderWindow* window);  // MENU HAS TO CHANGE
                                            // TO VISUALIZER
  virtual ~Sorting_Class();

  //SET STYLE FOR SORT ALGO
  void set_style(std::vector<std::string> variants, int y_pos);
  void insertion_sort();
  void selection_sort();
  void merge_sort();
  void exchange_sort();
  void distribution_sort();
  void concurrent_sort();
  void textbox(int char_size_textbox, std::size_t number_of_inputs, int pos_y);

  // RESPONSIBLE FOR CHANDELING INPUTBOX
  void input_box_selected(int item);

  // SET STYLE FOR VISUALIZATION BUTTONS
  void visualization_buttons_style(int pos_x);

  // VISUALIZE ALGORITHM WITH GIVEN ELEMENTS, MIN VALUE AND MAX VALUE
  void algo_viz(std::size_t n_elements, int min_val, int max_val);
  // OVERLOAD algo_viz(...) FUNCTION, ADDITIONAL PARAMETER case, WHERE false = WORST CASE
  void algo_viz(std::size_t n_elements, int min_val, int max_val, bool bw_case);

  //SET SHELL SORT PARAMS
  void set_shell_sort(int selected);

  // STATE OF PRESSED SORTING ALGORITHM CATEGORY
  enum class sort_cat {
    insertion,
    selection,
    merge,
    exchange,
    distribution,
    concurrent
  };

  // COMPARATOR FOR STD::PAIR<SORT_CAT, INT> TO BE USED IN THE MAP
  struct sort_cat_pair_comparator {
    bool operator()(const std::pair<sort_cat, int>& lhs,
                    const std::pair<sort_cat, int>& rhs) const {
      if (lhs.first != rhs.first)
        return lhs.first < rhs.first;  // Compare categories first
      return lhs.second < rhs.second;  // Then compare the index
    }
  };

  //FIND ALGO IN M_SORT_MAP
  void find_algo(int selected);

  //FIND OPTION IN M_SORT_CLASS_MAP
  void find_option(int selected);

  // INITALIZE SORTING OPTION SELECTOR
  void initalize_sorting_algos();

  // CHANGE OPTION PLACEMENT IN THE ARRAY
  void additional_option(bool additional);

  // SET DEFAULT OPTIONS SETTINGS
  void set_default_options();

  // SET LEFT/RIGHT BUTTONS
  void display_lr_buttons(bool display);

  // GET SELECTED SHELL GAP
  int get_shell_gap();

 private:
  // DISPLAYS SCREEN FOR SORTING
  Screen** current_screen;
  Visualizer* visualize;
  Visualization* final_visual;
  sf::RenderWindow* window_ptr;

  // RESPONSIBLE FOR KEYBOARD MOVEMENT
  int m_selected_sorting_algo_index;
  int m_selected_sort_algo;

  // CHOOSED ALGO, HOLDS VALUE OF SELECTED ALGO
  int m_choosed_algo;

  //STATE OF PRESSED SORTING ALGO CATEGORY
  sort_cat m_sc;
  //INITALIZE DIFFERENCT SORTING ALGOS LIST
  void initialize_insertion();
  void initialize_selection();
  void initialize_merge();
  void initialize_exchange();
  void initialize_distribution();
  void initialize_concurrent();
  // SORTING MAP(CATEGORY, INDEX)
  std::map<std::pair<sort_cat, int>, std::function<void()>,
           sort_cat_pair_comparator>
      m_sort_map;
  // SORTING CLASS MAP(M_SORT_MAP, OPTIONS, BUTTONS)
  std::unordered_map<int, std::function<void()>> m_sort_class_map;
  // CONSTANTS
  // LISTED IMPORTANT KEYS
  static constexpr int c_delete_key = 8;
  static constexpr int c_enter_key = 13;
  static constexpr int c_minus_key = 45;
  // HOLDING THE SIZE OF CERTAIN ELEMENTS
  static constexpr int c_headers = 3;
  static constexpr int c_input = 3;
  static constexpr int c_buttons = 4;

  // LIST OF ALGORITHMS VARIANTS, VARIES BY SORTING ALGORITHM
  // //STORES VARIANTS, OPTIONS, BUTTONS
  std::vector<sf::Text> m_algorithm_variants;
  std::size_t m_variants_size;  //STORES SIZE OF VARIANTS

  // TEXT STYLE & HEADERS
  int m_char_size_text_variants;
  std::array<std::string, c_headers> m_headers_text;
  std::array<sf::Text, c_headers> m_headers;

  // VISUALIZATION OPTIONS
  // THIS VECTOR KEEPS STATE OF:
  // NUMBER OF ELEMENTS, MINIMUM RANGE OF NUMBERS, MAXIMUM RANGE OF NUMBERS, OPTIONAL PARAMETER
  std::vector<int> m_visualization_options;
  std::vector<std::string> m_visualization_options_names;
  std::size_t m_option_size;

  // VISUALIZATION BUTTONS
  std::array<std::string, c_buttons> m_visualization_buttons_names;
  std::array<sf::Text, c_buttons> m_visualization_buttons_text;
  std::array<sf::RectangleShape, c_buttons> m_visualization_buttons_shape;

  // INPUT FOR OPTIONS
  std::array<sf::Text, c_input> m_textbox_input_style;
  std::ostringstream m_text_input;
  int m_selected_input_option;
  std::string m_temp_value;

  // IF THE IMPUT OPTION IS SELECTED
  bool m_possible_input;

  // KEEPS STATE IF ADDITIONAL PARAMETER IS OPEN
  bool m_additional_param;

  // LIST OF DIFFERENT SHELL SEQUENCE GAPS
  sf::Text m_gaps_seq;
  std::vector<std::string> m_gaps_seq_names;
  // KEEPS THE STATE OF CURRENT GAP INDEX
  int m_gaps_index;

  // SHAPE OF LEFT/RIGHT BUTTONS
  std::vector<sf::RectangleShape> m_lr_btn_shape;
  std::vector<sf::ConvexShape> m_triangle_arrow;
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

#endif
