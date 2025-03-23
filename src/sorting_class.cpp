#include "sorting_class.h"
#include "visualization.h"

Sorting_Class::Sorting_Class(Screen** screen_ptr, Visualizer* viz_ptr,
                             sf::RenderWindow* window)
    : current_screen(screen_ptr),
      visualize(viz_ptr),
      window_ptr(window),
      m_selected_sort_algo(0),
      m_selected_sorting_algo_index(0),
      m_char_size_text_variants(20),
      m_possible_input(false),
      m_temp_value(""),
      m_drop_down_item_font_size(15) {

  final_visual = new Visualization(screen_ptr, this, window_ptr);
  //INITIALIZE VISUALIZATION BUTTONS
  std::size_t number_of_buttons = 4;
  m_visualization_buttons_names = {"Start", "Example", "Worst case",
                                   "Best Case"};
  visualization_buttons_style(150);
  // INITALIZE VISUALIZATION OPTIONS VECTOR WITH VALUES:
  // NUMBER OF ELEMENTS = 10, MINIMUM RANGE OF ELEMENTS = 0, MAXIMUM RANGE OF ELEMENTS = 100
  std::size_t number_of_options = 3;
  m_visualization_options_names = {
      "Number of elemenst:", "Minimum value:", "Maximum value:"};
  m_visualization_options = {10, 0, 100};
  textbox(20, 3, 150);
  m_choosed_algo = 0;
}

Sorting_Class::~Sorting_Class() {
  delete final_visual;
}

void Sorting_Class::draw(sf::RenderWindow& window) {
  for (const auto& x : m_visualization_buttons_shape)
    window.draw(x);
  for (const auto& x : m_algorithm_variants)
    window.draw(x);
  for (const auto& x : m_headers)
    window.draw(x);
  for (const auto& x : m_textbox_input_style)
    window.draw(x);
  for (const auto& x : m_list_of_elements)
    window.draw(x);
}

void Sorting_Class::move_up() {
  if (!m_possible_input) {
    if (m_selected_sorting_algo_index - 1 >= 0) {
      if (m_selected_sorting_algo_index == m_variants_size - 1)
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::Red);
      else {
        if (m_selected_sorting_algo_index == m_choosed_algo)
          m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Blue);
        else
          m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
              sf::Color::White);
      }
      m_selected_sorting_algo_index--;
      m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
          sf::Color::Green);
      m_selected_sort_algo = m_selected_sorting_algo_index;
    }
  }
}

void Sorting_Class::move_down() {
  if (!m_possible_input) {
    if (m_selected_sorting_algo_index + 1 <
        c_options + m_variants_size + c_buttons) {
      if (m_selected_sorting_algo_index == m_variants_size - 1)
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::Red);
      else {
        if (m_selected_sorting_algo_index == m_choosed_algo)
          m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Blue);
        else
          m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
              sf::Color::White);
      }
      m_selected_sorting_algo_index++;
      m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
          sf::Color::Green);
      m_selected_sort_algo = m_selected_sorting_algo_index;
    }
  }
}

void Sorting_Class::move_left() {
  if (!m_possible_input && !m_dropped) {
    if (!(m_selected_sorting_algo_index < m_variants_size)) {
      if (m_selected_sorting_algo_index == m_variants_size - 1)
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::Red);
      else {
        if (m_choosed_algo == m_selected_sorting_algo_index)
          m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
              sf::Color::Blue);
        else
          m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
              sf::Color::White);
      }
      if (m_selected_sorting_algo_index > m_variants_size - 1 &&
          m_selected_sorting_algo_index <= c_options + m_variants_size - 1) {
        m_selected_sorting_algo_index = 0;
        m_selected_sort_algo = m_selected_sorting_algo_index;
        m_algorithm_variants[m_selected_sort_algo].setFillColor(
            sf::Color::Green);
      } else {
        m_selected_sorting_algo_index = m_variants_size;
        m_selected_sort_algo = m_selected_sorting_algo_index;
        m_algorithm_variants[m_selected_sort_algo].setFillColor(
            sf::Color::Green);
      }
    }
  }
}

void Sorting_Class::move_right() {
  if (!m_possible_input && !m_dropped) {
    if (!(m_selected_sorting_algo_index >= c_options + m_variants_size)) {
      if (m_selected_sorting_algo_index == m_variants_size - 1)
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::Red);
      else {
        if (m_choosed_algo == m_selected_sorting_algo_index)
          m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
              sf::Color::Blue);
        else
          m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
              sf::Color::White);
      }
      if (m_selected_sorting_algo_index < c_options + m_variants_size &&
          !(m_selected_sorting_algo_index >= m_variants_size)) {
        m_selected_sorting_algo_index = m_variants_size;
        m_selected_sort_algo = m_selected_sorting_algo_index;
        m_algorithm_variants[m_selected_sort_algo].setFillColor(
            sf::Color::Green);
      } else if (m_selected_sorting_algo_index < c_options + m_variants_size) {
        m_selected_sorting_algo_index = c_options + m_variants_size;
        m_selected_sort_algo = m_selected_sorting_algo_index;
        m_algorithm_variants[m_selected_sort_algo].setFillColor(
            sf::Color::Green);
      }
    }
  }
}

int Sorting_Class::pressed() {
  if (m_selected_sort_algo < 6 && m_selected_sort_algo != 0)
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::White);
  else if (m_selected_sort_algo == 0) {
    m_algorithm_variants[m_selected_sort_algo].setFillColor(sf::Color::Green);
    for (int i = 1; i < m_variants_size - 1; i++)
      m_algorithm_variants[i].setFillColor(sf::Color::White);
  }
  return m_selected_sort_algo;
}

void Sorting_Class::drop_down(int option) {
  switch (option) {
    case 2:
      m_choosed_algo = 2;
      std::vector<std::string> temp = {"Original Shell Sort",
                                       "Frank & Lazarus Gap",
                                       "Hibbard Gap",
                                       "Papernov & Stasevich Gap",
                                       "Pratt Gap",
                                       "Knuth Gap",
                                       "Incerpi & Sedgewick Gap",
                                       "Sedgewick Gap 1",
                                       "Sedgewick Gap 2",
                                       "Gonnet & Baeza-Yates Gap",
                                       "Tokuda Gap",
                                       "Lee Gap",
                                       "Skean & Ehrenborg & Jaromczyk Gap"};
      drop_down_list(temp.size(), temp, 2, 75, 150, 400);
      m_algorithm_variants[option].setFillColor(sf::Color::Green);
      break;
  }
}

void Sorting_Class::drop_down_list(std::size_t number_of_elements,
                                   std::span<std::string> list_of_algo,
                                   int end_iter, int add_val_pos_x_drop_down,
                                   int add_val_pos_y_before_ddm,
                                   int add_val_pos_y_after_ddm) {
  m_dropped = true;
  m_list_of_elements.resize(number_of_elements);
  Screen::set_sf_text_style(m_list_of_elements, list_of_algo,
                            m_drop_down_item_font_size, add_val_pos_x_drop_down,
                            275, false, true, 0, 20);
  for (int i = 0; i < m_variants_size; i++) {
    if (!(i > end_iter))
      m_algorithm_variants[i].setPosition(50,
                                          50 * i + add_val_pos_y_before_ddm);
    else
      m_algorithm_variants[i].setPosition(50, 50 * i + add_val_pos_y_after_ddm);
  }
}
void Sorting_Class::change_option(int selected) {
  switch (selected) {
    case 0:  // BASIC INSERTION SORT
      m_choosed_algo = 0;
      m_algorithm_variants[selected].setFillColor(sf::Color::Green);
      break;
    case 1:  // RECURSIVE INSERTION SORT
      m_choosed_algo = 1;
      m_algorithm_variants[selected].setFillColor(sf::Color::Green);
      break;
    case 2:  // SHELL SORT
      drop_down(selected);
      break;
    case 3:  // BINARY INSERTION SORT
      m_choosed_algo = 3;
      m_algorithm_variants[selected].setFillColor(sf::Color::Green);
      break;
    case 4:  // LIBRARY SORT
      m_choosed_algo = 4;
      m_algorithm_variants[selected].setFillColor(sf::Color::Green);
      break;
    case 5:
      m_choosed_algo = 0;
      m_selected_sort_algo = 0;
      m_selected_sorting_algo_index = 0;
      m_algorithm_variants[0].setFillColor(sf::Color::Green);
      m_algorithm_variants[m_algorithm_variants.size() - 1 -
                           m_visualization_options.size()]
          .setFillColor(sf::Color::Red);
      *current_screen = visualize;
      break;
    case 6:
      input_box_selected(0);
      break;
    case 7:
      input_box_selected(1);
      break;
    case 8:
      input_box_selected(2);
      break;
    case 9:
      algo_viz(m_visualization_options[0], m_visualization_options[1],
               m_visualization_options[2]);
      break;
    case 10:
      algo_viz(10, 0, 10);
      break;
    case 11:
      algo_viz(100, 0, 100, false);
      break;
    case 12:
      algo_viz(100, 0, 100, true);
      break;
  }
}

void Sorting_Class::set_style(std::vector<std::string> variants, int pos_y) {
  m_algorithm_variants.resize(variants.size());
  Screen::set_sf_text_style(m_algorithm_variants, variants,
                            m_char_size_text_variants, 50, pos_y, false, true,
                            0, 50);
  m_algorithm_variants[m_variants_size - 1].setFillColor(sf::Color::Red);
  m_algorithm_variants[0].setFillColor(sf::Color::Green);
  int count = 0;
  for (int i = m_variants_size; i < c_options + m_variants_size; i++) {
    m_algorithm_variants[i].setPosition(460, 50 * count + pos_y);
    count++;
  }
  count = 0;
  int temp = 0;
  for (int i = c_buttons + m_variants_size - 1;
       i < c_buttons + c_options + m_variants_size; i++) {
    m_algorithm_variants[i].setCharacterSize(35);
    sf::FloatRect text_bounds = m_algorithm_variants[i].getLocalBounds();
    m_algorithm_variants[i].setPosition(890 + (100 - text_bounds.width / 2),
                                        temp + 60 * count + pos_y);
    count++;
    temp = 100;
  }
  m_headers_text = {"Variants", "Options", "Visulization"};
  temp = 0;
  for (int i = 0; i < m_headers_text.size(); i++) {
    m_headers[i].setFont(m_open_sans);
    m_headers[i].setFillColor(sf::Color::White);
    m_headers[i].setCharacterSize(40);
    m_headers[i].setStyle(sf::Text::Bold);
    m_headers[i].setPosition(30 + temp * i, pos_y - 75);
    m_headers[i].setString(m_headers_text[i]);
    temp = 400;
  }
}

void Sorting_Class::insertion_sort() {
  std::vector<std::string> insertion_sort_variants = {
      "Insertion Sort", "Recursive Insertion Sort",
      "Shell Sort",     "Binary Insertion Sort",
      "Library Sort",   "Back"};
  m_algorithm_variants_names.clear();
  m_algorithm_variants_names.insert(m_algorithm_variants_names.end(),
                                    insertion_sort_variants.begin(),
                                    insertion_sort_variants.end());
  m_variants_size = insertion_sort_variants.size();
  insertion_sort_variants.insert(insertion_sort_variants.end(),
                                 m_visualization_options_names.begin(),
                                 m_visualization_options_names.end());
  insertion_sort_variants.insert(insertion_sort_variants.end(),
                                 m_visualization_buttons_names.begin(),
                                 m_visualization_buttons_names.end());
  set_style(insertion_sort_variants, 150);
}

void Sorting_Class::textbox(int char_size_textbox, std::size_t number_of_inputs,
                            int pos_y) {
  std::vector<std::string> temp(number_of_inputs);
  for (int i = 0; i < number_of_inputs; i++)
    temp[i] = std::to_string(m_visualization_options[i]);
  Screen::set_sf_text_style(m_textbox_input_style, temp,
                            m_char_size_text_variants, 690, pos_y, false, true,
                            0, 50);
}

void Sorting_Class::typed_on(sf::Event input) {
  if (m_possible_input) {
    int char_typed = input.text.unicode;
    if ((char_typed >= 48 && char_typed <= 57) || char_typed == c_delete_key ||
        char_typed == c_enter_key || char_typed == c_minus_key) {
      if (m_selected_input_option == 0 && char_typed == c_minus_key)
        std::cerr << "Number of elements, can't have negative value"
                  << std::endl;
      else
        input_logic(char_typed);
    }
  }
}

void Sorting_Class::input_box_selected(int item) {
  if (m_possible_input == true) {
    if (m_text_input.str() == "")
      m_textbox_input_style[m_selected_input_option].setString(
          std::to_string(m_visualization_options[m_selected_input_option]));
    else
      m_textbox_input_style[m_selected_input_option].setString(m_temp_value);
    std::from_chars(m_temp_value.data(),
                    m_temp_value.data() + m_temp_value.size(),
                    m_visualization_options[m_selected_input_option]);
    if (m_visualization_options[1] > m_visualization_options[2]) {
      std::cerr << "Minimum value of elements can't be greater than maximum "
                   "value of elements\nSetting default values"
                << std::endl;
      m_visualization_options[1] = 0;
      m_visualization_options[2] = 100;
      m_textbox_input_style[1].setString("0");
      m_textbox_input_style[2].setString("100");
    }
    m_text_input.str("");
    m_text_input.clear();
    m_possible_input = false;
    m_temp_value = "";
  } else {
    m_selected_input_option = item;
    m_possible_input = true;
  }
}

void Sorting_Class::visualization_buttons_style(int pos_y) {
  int temp = 0;
  for (int i = 0; i < m_visualization_buttons_text.size(); i++) {
    m_visualization_buttons_shape[i].setPosition(880, temp + 60 * i + pos_y);
    m_visualization_buttons_shape[i].setSize({220, 45});
    m_visualization_buttons_shape[i].setOutlineColor(sf::Color::Red);
    m_visualization_buttons_shape[i].setOutlineThickness(1.5);
    m_visualization_buttons_shape[i].setFillColor(sf::Color::Black);
    m_visualization_buttons_text[i].setPosition(
        890 + (100 - (m_visualization_buttons_names[i].length() * 35) / 2),
        temp + 60 * i + pos_y);
    temp = 100;
  }
}

void Sorting_Class::algo_viz(std::size_t n_elements, int min_val, int max_val) {
  *current_screen = final_visual;
  final_visual->set_options(n_elements, min_val, max_val,
                            m_algorithm_variants[m_choosed_algo].getString());
  final_visual->visual();
}

void Sorting_Class::algo_viz(std::size_t n_elements, int min_val, int max_val,
                             bool bw_case) {}
