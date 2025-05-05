#ifndef SEARCHCLASS_H
#define SEARCHCLASS_H
#pragma once

#include "visualizer.h"

class Search_Class : public Screen {
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

  Search_Class(Screen** screen_ptr, Visualizer* viz_ptr,
               sf::RenderWindow* window);  // MENU HAS TO CHANGE
                                           // TO VISUALIZER
  virtual ~Search_Class();

  //SET STYLE FOR SEARCH ALGO
  void set_style(std::vector<std::string> variants, int y_pos);
  void linear_search();
  void binary_search();
  void textbox(int char_size_textbox, std::size_t number_of_inputs, int pos_y);

  // RESPONSIBLE FOR CHANDELING INPUTBOX
  void input_box_selected(int item);

  // SET STYLE FOR VISUALIZATION BUTTONS
  void visualization_buttons_style(int pos_x);

  // VISUALIZE ALGORITHM WITH GIVEN ELEMENTS, MIN VALUE, MAX VALUE AND SEARCH NUMBER
  void algo_viz(std::size_t n_elements, int min_val, int max_val,
                int search_number);
  // OVERLOAD algo_viz(...) FUNCTION, ADDITIONAL PARAMETER case, WHERE false = WORST CASE
  void algo_viz(std::size_t n_elements, int min_val, int max_val,
                int search_number, bool bw_case);

  // SET INSERTION SEARCH PARAMS
  void set_selected_search_variants(int selected,
                                    std::function<void()> category_func,
                                    std::vector<std::string>& names,
                                    std::string name_of_input);

  // STATE OF PRESSED SEARCHING ALGORITHM CATEGORY
  enum class search_cat { linear, binary };

  // COMPARATOR FOR STD::PAIR<SEARCH_CAT, INT> TO BE USED IN THE MAP
  struct search_cat_pair_comparator {
    bool operator()(const std::pair<search_cat, int>& lhs,
                    const std::pair<search_cat, int>& rhs) const {
      if (lhs.first != rhs.first)
        return lhs.first < rhs.first;  // Compare categories first
      return lhs.second < rhs.second;  // Then compare the index
    }
  };

  // Custom hash function for std::pair<std::string, int>
  struct pair_hash {
    std::size_t operator()(const std::pair<std::string, int>& pair) const {
      auto hash1 = std::hash<std::string>{}(pair.first);
      auto hash2 = std::hash<int>{}(pair.second);
      return hash1 ^ (hash2 << 1);  // Combine the two hashes
    }
  };

  //FIND ALGO IN M_SEARCH_MAP
  void find_algo(int selected);

  //FIND OPTION IN M_SEARCH_CLASS_MAP
  void find_option(int selected);

  // SETS SETTINGS FOR SELECTED ALGO, PREPARATION FOR VISUALIZATION
  void set_setting_selected_algo(int selected, std::function<void()> func);

  // INITALIZE SEARCHING OPTION SELECTOR
  void initalize_searching_algos();

  // CHANGE OPTION PLACEMENT IN THE ARRAY
  void additional_option(bool additional);

  // SET DEFAULT OPTIONS SETTINGS
  void set_default_options();

  // SET LEFT/RIGHT BUTTONS
  void display_lr_buttons(bool display);

  // GET SELECTED ADDITIONAL OPTION INDEX
  int get_additional_option_index();

  // GET FULL NAME OF SELECTED ALGO
  std::string get_display_name();

  // HASH MAP FOR FULL ALGORITHMS NAMES WITH ITS VARIANTS
  std::unordered_map<std::pair<std::string, int>, std::string, pair_hash>
      m_display_name;

 private:
  // DISPLAYS SCREEN FOR SERACHING
  Screen** current_screen;
  Visualizer* visualize;
  Visualization* final_visual;
  sf::RenderWindow* window_ptr;

  // RESPONSIBLE FOR KEYBOARD MOVEMENT
  int m_selected_searching_algo_index;
  int m_selected_search_algo;

  // CHOOSED ALGO, HOLDS VALUE OF SELECTED ALGO
  int m_choosed_algo;

  //STATE OF PRESSED SEARCHING ALGO CATEGORY
  search_cat m_sc;
  //INITALIZE DIFFERENCT SEARCHING ALGOS LIST
  void initialize_linear();
  void initialize_binary();
  void initialize_concurrent();
  // SEARCHING MAP(CATEGORY, INDEX)
  std::map<std::pair<search_cat, int>, std::function<void()>,
           search_cat_pair_comparator>
      m_search_map;
  // SEARCHING CLASS MAP(M_SEARCH_MAP, OPTIONS, BUTTONS)
  std::unordered_map<int, std::function<void()>> m_search_class_map;
  // CONSTANTS
  // LISTED IMPORTANT KEYS
  static constexpr int c_delete_key = 8;
  static constexpr int c_enter_key = 13;
  static constexpr int c_minus_key = 45;
  // HOLDING THE SIZE OF CERTAIN ELEMENTS
  static constexpr int c_headers = 3;
  static constexpr int c_input = 4;
  static constexpr int c_buttons = 4;

  // LIST OF ALGORITHMS VARIANTS, VARIES BY SEARCHING ALGORITHM
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
  size_t m_option_size;

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

  // KEEPS STATE IF ADDIOTIONAL PARAMETER EXISTS
  bool m_additional_exists;

  // LIST OF ADDITIONAL OPTION PARAMS
  sf::Text m_additional_option;
  std::vector<std::string> m_additional_option_names;

  // KEEPS THE STATE OF CURRENT ADDITIONAL OPTION INDEX
  int m_additional_option_index;

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
