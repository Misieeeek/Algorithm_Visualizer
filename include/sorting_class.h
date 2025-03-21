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
  void drop_down(int option) override;
  void typed_on(sf::Event input) override;

  Sorting_Class(Screen** screen_ptr, Visualizer* viz_ptr,
                sf::RenderWindow* window);  // MENU HAS TO CHANGE
                                            // TO VISUALIZER
  virtual ~Sorting_Class();

  void set_style(std::vector<std::string> variants, int y_pos);
  void insertion_sort();
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

 private:
  // DISPLAYS SCREEN FOR SORTING
  Screen** current_screen;
  Visualizer* visualize;
  Visualization* final_visual;
  sf::RenderWindow* window_ptr;
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

  // TEXT STYLE & HEADERS
  int m_char_size_text_variants;
  std::array<std::string, c_headers> m_headers_text;
  std::array<sf::Text, c_headers> m_headers;

  // VISUALIZATION OPTIONS
  // THIS VECTOR KEEPS STATE OF:
  // NUMBER OF ELEMENTS, MINIMUM RANGE OF NUMBERS, MAXIMUM RANGE OF NUMBERS, OPTIONAL PARAMETER
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

#endif
