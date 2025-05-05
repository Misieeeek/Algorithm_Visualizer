#include "search_class.h"
#include "visualization.h"

Search_Class::Search_Class(Screen** screen_ptr, Visualizer* viz_ptr,
                           sf::RenderWindow* window)
    : current_screen(screen_ptr),
      visualize(viz_ptr),
      window_ptr(window),
      m_selected_search_algo(0),
      m_selected_searching_algo_index(0),
      m_char_size_text_variants(20),
      m_possible_input(false),
      m_temp_value(""),
      m_option_size(4),
      m_additional_param(false),
      m_additional_exists(false) {

  final_visual = new Visualization(screen_ptr, this, window_ptr);
  //INITIALIZE VISUALIZATION BUTTONS
  m_visualization_buttons_names = {"Start", "Example", "Worst case",
                                   "Best Case"};
  visualization_buttons_style(150);
  // INITALIZE VISUALIZATION OPTIONS VECTOR WITH VALUES:
  // NUMBER OF ELEMENTS = 10, MINIMUM RANGE OF ELEMENTS = 0, MAXIMUM RANGE OF ELEMENTS = 100, SEARCHING VALUE = RANDOM/0
  m_visualization_options_names = {"Number of elemenst:", "Minimum value:",
                                   "Maximum value:", "Searching value: "};
  m_visualization_options = {10, 0, 100, 5};  //TODO: RANDOM
  textbox(20, c_input, 150);
  m_choosed_algo = 0;
  m_lr_btn_shape.resize(0);
  m_triangle_arrow.resize(0);
  m_additional_option_index = 0;
}

Search_Class::~Search_Class() {
  delete final_visual;
}

void Search_Class::draw(sf::RenderWindow& window) {
  for (const auto& x : m_visualization_buttons_shape)
    window.draw(x);
  for (const auto& x : m_algorithm_variants)
    window.draw(x);
  for (const auto& x : m_headers)
    window.draw(x);
  for (const auto& x : m_textbox_input_style)
    window.draw(x);
  for (const auto& x : m_lr_btn_shape)
    window.draw(x);
  for (const auto& x : m_triangle_arrow)
    window.draw(x);
  window.draw(m_additional_option);
}

void Search_Class::move_up() {
  if (!m_possible_input && !m_additional_param) {
    if (m_selected_searching_algo_index - 1 >= 0) {
      if (m_selected_searching_algo_index == m_variants_size - 1)
        m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
            sf::Color::Red);
      else {
        if (m_selected_searching_algo_index == m_choosed_algo)
          m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Blue);
        else
          m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
              sf::Color::White);
      }
      m_selected_searching_algo_index--;
      m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
          sf::Color::Green);
      m_selected_search_algo = m_selected_searching_algo_index;
    }
  }
}

void Search_Class::move_down() {
  if (!m_possible_input && !m_additional_param) {
    if (m_selected_searching_algo_index + 1 <
        m_option_size + m_variants_size + c_buttons) {
      if (m_selected_searching_algo_index == m_variants_size - 1)
        m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
            sf::Color::Red);
      else {
        if (m_selected_searching_algo_index == m_choosed_algo)
          m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Blue);
        else
          m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
              sf::Color::White);
      }
      m_selected_searching_algo_index++;
      m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
          sf::Color::Green);
      m_selected_search_algo = m_selected_searching_algo_index;
    }
  }
}

void Search_Class::move_left() {
  if (!m_possible_input) {
    if (m_additional_param) {
      if (m_additional_option_index > 0) {
        m_additional_option_index--;
        float text_width =
            m_additional_option_names[m_additional_option_index].length() * 5;
        float min_x = 630;
        float max_x = 780;
        float center_x = (min_x + max_x) / 2;
        m_additional_option.setPosition(center_x - text_width / 2, 310);
        m_additional_option.setString(
            m_additional_option_names[m_additional_option_index]);
      }
    } else {
      if (!(m_selected_searching_algo_index < m_variants_size)) {
        if (m_selected_searching_algo_index == m_variants_size - 1)
          m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
              sf::Color::Red);
        else {
          if (m_choosed_algo == m_selected_searching_algo_index)
            m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
                sf::Color::Blue);
          else
            m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
                sf::Color::White);
        }
        if (m_selected_searching_algo_index > m_variants_size - 1 &&
            m_selected_searching_algo_index <=
                m_algorithm_variants.size() - c_buttons - 1) {
          m_selected_searching_algo_index = 0;
          m_selected_search_algo = m_selected_searching_algo_index;
          m_algorithm_variants[m_selected_search_algo].setFillColor(
              sf::Color::Green);
        } else {
          m_selected_searching_algo_index = m_variants_size;
          m_selected_search_algo = m_selected_searching_algo_index;
          m_algorithm_variants[m_selected_search_algo].setFillColor(
              sf::Color::Green);
        }
      }
    }
  }
}

void Search_Class::move_right() {
  if (!m_possible_input) {
    if (m_additional_param) {
      if (m_additional_option_index < m_additional_option_names.size() - 1) {
        m_additional_option_index++;
        float text_width =
            m_additional_option_names[m_additional_option_index].length() * 5;
        float min_x = 630;
        float max_x = 780;
        float center_x = (min_x + max_x) / 2;
        m_additional_option.setPosition(center_x - text_width / 2, 310);
        m_additional_option.setString(
            m_additional_option_names[m_additional_option_index]);
      }
    } else {
      if (!(m_selected_searching_algo_index >=
            m_algorithm_variants.size() - c_buttons)) {
        if (m_selected_searching_algo_index == m_variants_size - 1)
          m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
              sf::Color::Red);
        else {
          if (m_choosed_algo == m_selected_searching_algo_index)
            m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
                sf::Color::Blue);
          else
            m_algorithm_variants[m_selected_searching_algo_index].setFillColor(
                sf::Color::White);
        }
        if (m_selected_searching_algo_index <
                m_algorithm_variants.size() - c_buttons &&
            !(m_selected_searching_algo_index >= m_variants_size)) {
          m_selected_searching_algo_index = m_variants_size;
          m_selected_search_algo = m_selected_searching_algo_index;
          m_algorithm_variants[m_selected_search_algo].setFillColor(
              sf::Color::Green);
        } else if (m_selected_searching_algo_index <
                   m_algorithm_variants.size() - c_buttons) {
          m_selected_searching_algo_index =
              m_algorithm_variants.size() - c_buttons;
          m_selected_search_algo = m_selected_searching_algo_index;
          m_algorithm_variants[m_selected_search_algo].setFillColor(
              sf::Color::Green);
        }
      }
    }
  }
}

int Search_Class::pressed() {
  if (m_selected_search_algo < 6 && m_selected_search_algo != 0)
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::White);
  else if (m_selected_search_algo == 0) {
    m_algorithm_variants[m_selected_search_algo].setFillColor(sf::Color::Green);
    for (int i = 1; i < m_variants_size - 1; i++)
      m_algorithm_variants[i].setFillColor(sf::Color::White);
  }
  return m_selected_search_algo;
}

void Search_Class::set_default_options() {
  m_option_size = 4;
  m_visualization_options_names.resize(m_option_size);
  m_visualization_options_names = {"Number of elemenst:", "Minimum value:",
                                   "Maximum value:", "Searching value: "};
}

void Search_Class::additional_option(bool additional) {
  m_additional_option.setString("");
  display_lr_buttons(false);
  m_search_class_map[m_variants_size] = [this]() {
    input_box_selected(0);
  };
  m_search_class_map[m_variants_size + 1] = [this]() {
    input_box_selected(1);
  };
  m_search_class_map[m_variants_size + 2] = [this]() {
    input_box_selected(2);
  };
  m_search_class_map[m_variants_size + 3] = [this]() {
    input_box_selected(3);
  };
  int i = (additional) ? 1 : 0;
  if (additional) {
    m_additional_option.setString(
        m_additional_option_names[m_additional_option_index]);
    m_search_class_map[m_variants_size + 4] = [this]() {
      if (m_additional_param) {
        m_additional_param = false;
        display_lr_buttons(false);
      } else {
        display_lr_buttons(true);
        m_additional_param = true;
      }
    };
  }
  m_search_class_map[m_variants_size + 4 + i] = [this]() {
    algo_viz(m_visualization_options[0], m_visualization_options[1],
             m_visualization_options[2], m_visualization_options[3]);
  };
  m_search_class_map[m_variants_size + 5 + i] = [this]() {
    algo_viz(10, 0, 10, 5);  // TODO: CHANGE TO RANDOM
  };
  m_search_class_map[m_variants_size + 6 + i] = [this]() {
    algo_viz(100, 0, 100, 5, false);  // TODO: CHANGE TO RANDOM
  };
  m_search_class_map[m_variants_size + 7 + i] = [this]() {
    algo_viz(100, 0, 100, 5, true);  // TODO: CHANGE TO RANDOM
  };
}

void Search_Class::display_lr_buttons(bool display) {
  if (display) {
    m_lr_btn_shape.resize(2);
    m_triangle_arrow.resize(2);
    for (int i = 0; i < 2; i++) {
      m_lr_btn_shape[i].setSize({20, 20});
      m_lr_btn_shape[i].setFillColor(sf::Color::Black);
      m_lr_btn_shape[i].setOutlineColor(sf::Color::White);
      m_lr_btn_shape[i].setOutlineThickness(1.5);
      m_triangle_arrow[i].setPointCount(3);
      m_triangle_arrow[i].setFillColor(sf::Color::Red);
      m_triangle_arrow[i].setOutlineThickness(1);
      m_triangle_arrow[i].setOutlineColor(sf::Color::Black);
    }
    m_triangle_arrow[0].setPoint(0, sf::Vector2f(635, 315));
    m_triangle_arrow[0].setPoint(1, sf::Vector2f(645, 310));
    m_triangle_arrow[0].setPoint(2, sf::Vector2f(645, 320));
    m_triangle_arrow[1].setPoint(0, sf::Vector2f(795, 315));
    m_triangle_arrow[1].setPoint(1, sf::Vector2f(785, 310));
    m_triangle_arrow[1].setPoint(2, sf::Vector2f(785, 320));
    m_lr_btn_shape[0].setPosition({630, 305});
    m_lr_btn_shape[1].setPosition({780, 305});
  } else {
    m_lr_btn_shape.resize(0);
    m_triangle_arrow.resize(0);
  }
}

int Search_Class::get_additional_option_index() {
  return m_additional_option_index;
}

void Search_Class::set_selected_search_variants(
    int selected, std::function<void()> category_func,
    std::vector<std::string>& names, std::string name_of_input) {
  m_additional_option_index = 0;
  m_choosed_algo = selected;
  m_option_size = 4;
  m_visualization_options_names.resize(m_option_size);
  m_visualization_options_names[3] = name_of_input;
  m_additional_option_names.clear();
  for (auto& x : names)
    m_additional_option_names.push_back(x);
  category_func();
  for (auto& x : m_algorithm_variants)
    x.setFillColor(sf::Color::White);
  m_algorithm_variants[m_variants_size - 1].setFillColor(sf::Color::Red);
  m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  additional_option(true);
  m_additional_option.setFont(m_open_sans);
  m_additional_option.setFillColor(sf::Color::White);
  m_additional_option.setCharacterSize(10);
  m_additional_option.setStyle(sf::Text::Bold);
  float text_width =
      m_additional_option_names[m_additional_option_index].length() * 5;
  float min_x = 630;
  float max_x = 780;
  float center_x = (min_x + max_x) / 2;
  m_additional_option.setPosition(center_x - text_width / 2, 310);
  m_additional_option.setString(
      m_additional_option_names[m_additional_option_index]);
}

void Search_Class::set_setting_selected_algo(int selected,
                                             std::function<void()> func) {
  m_additional_exists = false;
  m_choosed_algo = selected;
  set_default_options();
  additional_option(false);
  func();
  m_algorithm_variants[0].setFillColor(sf::Color::White);
  m_algorithm_variants[selected].setFillColor(sf::Color::Green);
}

void Search_Class::initalize_searching_algos() {
  initialize_linear();
  initialize_binary();
}

void Search_Class::initialize_linear() {
  m_search_map[{search_cat::linear, 0}] = [this]() {  // LINEAR SEARCH
    set_setting_selected_algo(0, [this]() { linear_search(); });
  };
  additional_option(false);
}

void Search_Class::initialize_binary() {
  m_search_map[{search_cat::binary, 0}] = [this]() {  // BINARY SEARCH
    set_setting_selected_algo(0, [this]() { binary_search(); });
  };
  additional_option(false);
}

void Search_Class::find_algo(int selected) {
  auto it = m_search_map.find(std::make_pair(m_sc, selected));
  if (it != m_search_map.end()) {
    it->second();
  } else {
    std::cerr << "Algorithm not found" << std::endl;
  }
}

void Search_Class::find_option(int selected) {
  auto it = m_search_class_map.find(selected);
  if (it != m_search_class_map.end()) {
    it->second();
  } else {
    std::cerr << "Option not found" << std::endl;
  }
}

void Search_Class::change_option(int selected) {
  if (selected == m_variants_size - 1) {
    m_choosed_algo = 0;
    m_selected_search_algo = 0;
    m_selected_searching_algo_index = 0;
    m_algorithm_variants[0].setFillColor(sf::Color::Green);
    m_algorithm_variants[m_variants_size].setFillColor(sf::Color::Red);
    set_default_options();
    *current_screen = visualize;
  } else if (selected > m_variants_size - 1) {
    find_option(selected);
  } else {
    find_algo(selected);
  }
}

void Search_Class::set_style(std::vector<std::string> variants, int pos_y) {
  m_algorithm_variants.resize(variants.size());
  Screen::set_sf_text_style(m_algorithm_variants, variants,
                            m_char_size_text_variants, 50, pos_y, false, true,
                            0, 50);
  m_algorithm_variants[m_variants_size - 1].setFillColor(sf::Color::Red);
  m_algorithm_variants[0].setFillColor(sf::Color::Green);
  int count = 0;
  for (int i = m_variants_size; i < m_algorithm_variants.size() - c_buttons;
       i++) {
    m_algorithm_variants[i].setPosition(460, 50 * count + pos_y);
    count++;
  }
  count = 0;
  int temp = 0;
  for (int i = m_algorithm_variants.size() - c_buttons;
       i < m_algorithm_variants.size(); i++) {
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

void Search_Class::linear_search() {
  std::vector<std::string> linear_search_variants = {"Linear Search", "Back"};
  m_variants_size = linear_search_variants.size();
  linear_search_variants.insert(linear_search_variants.end(),
                                m_visualization_options_names.begin(),
                                m_visualization_options_names.end());
  linear_search_variants.insert(linear_search_variants.end(),
                                m_visualization_buttons_names.begin(),
                                m_visualization_buttons_names.end());
  set_style(linear_search_variants, 150);
  m_sc = search_cat::linear;
}

void Search_Class::binary_search() {
  std::vector<std::string> linear_search_variants = {"Binary Search", "Back"};
  m_variants_size = linear_search_variants.size();
  linear_search_variants.insert(linear_search_variants.end(),
                                m_visualization_options_names.begin(),
                                m_visualization_options_names.end());
  linear_search_variants.insert(linear_search_variants.end(),
                                m_visualization_buttons_names.begin(),
                                m_visualization_buttons_names.end());
  set_style(linear_search_variants, 150);
  m_sc = search_cat::binary;
}

void Search_Class::textbox(int char_size_textbox, size_t number_of_inputs,
                           int pos_y) {
  std::vector<std::string> temp(number_of_inputs);
  for (int i = 0; i < number_of_inputs; i++)
    temp[i] = std::to_string(m_visualization_options[i]);
  Screen::set_sf_text_style(m_textbox_input_style, temp,
                            m_char_size_text_variants, 690, pos_y, false, true,
                            0, 50);
}

void Search_Class::typed_on(sf::Event input) {
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

void Search_Class::input_box_selected(int item) {
  if (m_possible_input == true) {
    if (m_text_input.str() == "")
      m_textbox_input_style[m_selected_input_option].setString(
          std::to_string(m_visualization_options[m_selected_input_option]));
    else
      m_textbox_input_style[m_selected_input_option].setString(m_temp_value);
    std::from_chars(m_temp_value.data(),
                    m_temp_value.data() + m_temp_value.size(),
                    m_visualization_options[m_selected_input_option]);
    if (m_visualization_options[1] > m_visualization_options[2] ||
        m_visualization_options[2] < m_visualization_options[3] ||
        m_visualization_options[1] > m_visualization_options[3]) {
      std::cerr
          << "Minimum value of elements can't be greater than maximum value "
             "and seeking value can't be greater than maximum value and "
             "smaller than minimum value of elements"
             "value of elements\nSetting default values"
          << std::endl;
      m_visualization_options[1] = 0;
      m_visualization_options[2] = 100;
      m_visualization_options[3] = 0;  //TODO: SET BACK TO RANDOM
      m_textbox_input_style[1].setString("0");
      m_textbox_input_style[2].setString("100");
      m_textbox_input_style[3].setString("0");  //TODO: SET BACK TO RANDOM
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

void Search_Class::visualization_buttons_style(int pos_y) {
  int temp = 0;
  for (int i = 0; i < m_visualization_buttons_text.size(); i++) {
    m_visualization_buttons_shape[i].setPosition(880, temp + 60 * i + pos_y);
    m_visualization_buttons_shape[i].setSize({220, 45});
    m_visualization_buttons_shape[i].setOutlineColor(sf::Color::Red);
    m_visualization_buttons_shape[i].setOutlineThickness(1.5);
    m_visualization_buttons_shape[i].setFillColor(sf::Color::Black);
    m_visualization_buttons_text[i].setPosition(
        890 + (100 - (m_visualization_buttons_names[i].length() * 35) / 2.0),
        temp + 60 * i + pos_y);
    temp = 100;
  }
}

std::string Search_Class::get_display_name() {
  m_display_name[std::make_pair(std::string("Linear Search"), 0)] =
      "Linear Search";
  m_display_name[std::make_pair(std::string("Binary Search"), 0)] =
      "Binary Search";
  if (auto search = m_display_name.find(
          std::make_pair(m_algorithm_variants[m_choosed_algo].getString(),
                         m_additional_option_index));
      search != m_display_name.end())
    return search->second;
  else {
    std::cerr << "Name not found" << std::endl;
    return "Unknown Algorithm";
  }
}

void Search_Class::algo_viz(std::size_t n_elements, int min_val, int max_val,
                            int search_number) {
  *current_screen = final_visual;
  std::string algo_name;
  if (m_additional_exists == true)
    algo_name = get_display_name();
  else
    algo_name = m_algorithm_variants[m_choosed_algo].getString();
  std::cout << algo_name << '\n';
  final_visual->set_options(n_elements, min_val, max_val, search_number,
                            algo_name);
  final_visual->visual();
}

void Search_Class::algo_viz(std::size_t n_elements, int min_val, int max_val,
                            int search_number, bool bw_case) {}
