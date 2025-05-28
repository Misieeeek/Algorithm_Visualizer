#include <memory>
#include "visualization.h"
#include "visualization_options.h"

std::shared_ptr<Screen> Visualization_Options::g_dummy_screen = nullptr;

Visualization_Options::Visualization_Options()
    : current_screen(g_dummy_screen),
      visualize(nullptr),
      window_ptr(nullptr),
      final_visual(nullptr),
      m_selected_algo_index(),
      m_choosed_algo(),
      m_asc(),
      m_sort_class_map(),
      m_algo_map(),
      m_algorithm_variants(),
      m_all_options_size(),
      m_char_size_text_variants(),
      m_headers_text(),
      m_headers(),
      m_visualization_options_names(),
      m_visualization_options(),
      m_option_size(),
      m_visualization_buttons_names(),
      m_visualization_buttons_shape(),
      m_visualization_buttons_text(),
      m_text_input(),
      m_textbox_input_style(),
      m_selected_input_option(),
      m_possible_input(),
      m_temp_value(),
      m_additional_exists(),
      m_additional_param(),
      m_additional_option_index(0),
      m_additional_option(),
      m_additional_option_names(),
      m_lr_btn_shape(),
      m_triangle_arrow(),
      m_added_options() {}

Visualization_Options::Visualization_Options(
    std::shared_ptr<Screen>& screen_ptr, std::shared_ptr<Visualizer> viz_ptr,
    sf::RenderWindow* window)
    : current_screen(screen_ptr),
      visualize(viz_ptr),
      window_ptr(window),
      m_selected_algo_index(0),
      m_char_size_text_variants(20),
      m_possible_input(false),
      m_temp_value(""),
      m_option_size(3),
      m_additional_param(false),
      m_additional_exists(true),
      m_added_options() {

  //INITIALIZE VISUALIZATION BUTTONS
  m_visualization_buttons_names = {"Start", "Example", "Worst case",
                                   "Best Case"};
  visualization_buttons_style(150);
  // INITALIZE VISUALIZATION OPTIONS VECTOR WITH VALUES:
  // NUMBER OF ELEMENTS = 10, MINIMUM RANGE OF ELEMENTS = 0, MAXIMUM RANGE OF ELEMENTS = 100
  m_visualization_options_names = {
      "Number of elements:", "Minimum value:", "Maximum value:"};
  m_visualization_options = {10, 0, 100};
  textbox(m_char_size_text_variants, m_option_size, 150);
  m_choosed_algo = 0;
  m_lr_btn_shape.resize(0);
  m_triangle_arrow.resize(0);
  m_additional_option_index = 0;
}

void Visualization_Options::init_visualization_default() {
  final_visual = std::make_shared<Visualization>();
}

void Visualization_Options::init_visualization() {
  final_visual = std::make_shared<Visualization>(
      current_screen, shared_from_this(), window_ptr);
}

void Visualization_Options::draw(sf::RenderWindow& window) {
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

void Visualization_Options::move_up() {
  if (!m_possible_input && !m_additional_param) {
    if (m_selected_algo_index - 1 >= 0) {
      if (m_selected_algo_index == m_variants_size - 1)
        m_algorithm_variants[m_selected_algo_index].setFillColor(
            sf::Color::Red);
      else {
        if (m_selected_algo_index == m_choosed_algo)
          m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Blue);
        else
          m_algorithm_variants[m_selected_algo_index].setFillColor(
              sf::Color::White);
      }
      m_selected_algo_index--;
      m_algorithm_variants[m_selected_algo_index].setFillColor(
          sf::Color::Green);
    }
  }
}

void Visualization_Options::move_down() {
  if (!m_possible_input && !m_additional_param) {
    if (m_selected_algo_index + 1 <
        m_option_size + m_variants_size + c_buttons) {
      if (m_selected_algo_index == m_variants_size - 1)
        m_algorithm_variants[m_selected_algo_index].setFillColor(
            sf::Color::Red);
      else {
        if (m_selected_algo_index == m_choosed_algo)
          m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Blue);
        else
          m_algorithm_variants[m_selected_algo_index].setFillColor(
              sf::Color::White);
      }
      m_selected_algo_index++;
      m_algorithm_variants[m_selected_algo_index].setFillColor(
          sf::Color::Green);
    }
  }
}

void Visualization_Options::move_left() {
  if (!m_possible_input) {
    if (m_additional_param) {
      if (m_additional_option_index > 0) {
        m_additional_option_index--;
        make_lr_button_disappear();
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
      if (!(m_selected_algo_index < m_variants_size)) {
        if (m_selected_algo_index == m_variants_size - 1)
          m_algorithm_variants[m_selected_algo_index].setFillColor(
              sf::Color::Red);
        else {
          if (m_choosed_algo == m_selected_algo_index)
            m_algorithm_variants[m_selected_algo_index].setFillColor(
                sf::Color::Blue);
          else
            m_algorithm_variants[m_selected_algo_index].setFillColor(
                sf::Color::White);
        }
        if (m_selected_algo_index > m_variants_size - 1 &&
            m_selected_algo_index <= m_all_options_size - c_buttons - 1) {
          m_selected_algo_index = 0;
          m_algorithm_variants[m_selected_algo_index].setFillColor(
              sf::Color::Green);
        } else {
          m_selected_algo_index = m_variants_size;
          m_algorithm_variants[m_selected_algo_index].setFillColor(
              sf::Color::Green);
        }
      }
    }
  }
}

void Visualization_Options::move_right() {
  if (!m_possible_input) {
    if (m_additional_param) {
      if (m_additional_option_index < m_additional_option_names.size() - 1) {
        m_additional_option_index++;
        make_lr_button_disappear();
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
      if (!(m_selected_algo_index >= m_all_options_size - c_buttons)) {
        if (m_selected_algo_index == m_variants_size - 1)
          m_algorithm_variants[m_selected_algo_index].setFillColor(
              sf::Color::Red);
        else {
          if (m_choosed_algo == m_selected_algo_index)
            m_algorithm_variants[m_selected_algo_index].setFillColor(
                sf::Color::Blue);
          else
            m_algorithm_variants[m_selected_algo_index].setFillColor(
                sf::Color::White);
        }
        if (m_selected_algo_index < m_all_options_size - c_buttons &&
            !(m_selected_algo_index >= m_variants_size)) {
          m_selected_algo_index = m_variants_size;
          m_algorithm_variants[m_selected_algo_index].setFillColor(
              sf::Color::Green);
        } else if (m_selected_algo_index < m_all_options_size - c_buttons) {
          m_selected_algo_index = m_all_options_size - c_buttons;
          m_algorithm_variants[m_selected_algo_index].setFillColor(
              sf::Color::Green);
        }
      }
    }
  }
}

int Visualization_Options::pressed() {
  if (m_selected_algo_index < m_variants_size && m_selected_algo_index != 0)
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::White);
  else if (m_selected_algo_index == 0) {
    m_algorithm_variants[m_selected_algo_index].setFillColor(sf::Color::Green);
    for (int i = 1; i < m_variants_size - 1; i++)
      m_algorithm_variants[i].setFillColor(sf::Color::White);
  }
  return m_selected_algo_index;
}

void Visualization_Options::set_default_options() {
  m_option_size = 3;
  m_visualization_options_names.resize(m_option_size);
  m_visualization_options_names = {
      "Number of elements:", "Minimum value:", "Maximum value:"};
  for (int i = 0; i < 3; ++i) {
    m_sort_class_map[m_variants_size + i] = [this, i]() {
      input_box_selected(i);
    };
  }
}

void Visualization_Options::set_input_params_is() {
  set_default_options();
  m_added_options = 0;
}

void Visualization_Options::set_input_params_ss() {
  set_default_options();
  m_added_options = 0;
}

void Visualization_Options::set_input_params_ms() {
  set_default_options();
  m_added_options = 0;
}

void Visualization_Options::set_input_params_es() {
  set_default_options();
  m_added_options = 0;
}

void Visualization_Options::set_input_params_ds() {
  set_default_options();
  m_added_options = 0;
}

void Visualization_Options::set_input_params_cs() {
  set_default_options();
  m_added_options = 0;
}

void Visualization_Options::set_input_params_ls() {
  m_added_options = 1;
  m_option_size = 4;
  m_visualization_options_names.resize(m_option_size);
  m_visualization_options_names = {"Number of elements:", "Minimum value:",
                                   "Maximum value:", "Search value:"};
  m_visualization_options[3] = 5;
  for (int i = 0; i < 4; ++i) {
    m_sort_class_map[m_variants_size + i] = [this, i]() {
      input_box_selected(i);
    };
  }
}

void Visualization_Options::set_input_params_bs() {
  m_added_options = 1;
  m_option_size = 4;
  m_visualization_options_names = {"Number of elements:", "Minimum value:",
                                   "Maximum value:", "Search value:"};
  m_visualization_options[3] = 5;
  for (int i = 0; i < m_option_size; ++i) {
    m_sort_class_map[m_variants_size + i] = [this, i]() {
      input_box_selected(i);
    };
  }
}

void Visualization_Options::set_input_params_by_sub_category() {
  switch (m_asc) {
    case algo_subcat::insertion_sort:
      set_input_params_is();
      break;
    case algo_subcat::selection_sort:
      set_input_params_ss();
      break;
    case algo_subcat::merge_sort:
      set_input_params_ms();
      break;
    case algo_subcat::exchange_sort:
      set_input_params_es();
      break;
    case algo_subcat::distribution_sort:
      set_input_params_ds();
      break;
    case algo_subcat::concurrent_sort:
      set_input_params_cs();
      break;
    case algo_subcat::linear_search:
      set_input_params_ls();
      break;
    case algo_subcat::binary_search:
      set_input_params_bs();
      break;
  }
}

//TODO:: fix to be more abstract (begin from the end)
void Visualization_Options::additional_option(bool additional) {
  m_additional_option.setString("");
  display_lr_buttons(false);
  set_input_params_by_sub_category();
  int i = (additional) ? 1 : 0;
  if (additional) {
    m_additional_option.setString(
        m_additional_option_names[m_additional_option_index]);
    m_sort_class_map[m_variants_size + 3 + m_added_options] = [this]() {
      if (m_additional_param) {
        m_additional_param = false;
        display_lr_buttons(false);
      } else {
        display_lr_buttons(true);
        m_additional_param = true;
      }
    };
  }
  m_sort_class_map[m_variants_size + 3 + i + m_added_options] = [this]() {
    std::cout << "start\n";
    algo_viz(m_visualization_options[0], m_visualization_options[1],
             m_visualization_options[2]);
  };
  m_sort_class_map[m_variants_size + 4 + i + m_added_options] = [this]() {
    std::cout << "ex\n";
    algo_viz(10, 0, 10);
  };
  m_sort_class_map[m_variants_size + 5 + i + m_added_options] = [this]() {
    std::cout << "worst\n";
    algo_viz(100, 0, 100, false);
  };
  m_sort_class_map[m_variants_size + 6 + i + m_added_options] = [this]() {
    std::cout << "best\n";
    algo_viz(100, 0, 100, true);
  };
}

void Visualization_Options::set_selected_algo_variants(
    int selected, std::function<void()> category_func,
    std::vector<std::string>& names, size_t opt_size, std::string name_of_input,
    bool additional) {
  m_additional_option_index = 0;
  m_choosed_algo = selected;
  m_option_size = opt_size;
  m_visualization_options_names.resize(m_option_size);
  m_visualization_options_names[m_option_size - 1] = name_of_input;
  if (additional) {
    m_additional_option_names = names;
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
  category_func();
  for (auto& x : m_algorithm_variants)
    x.setFillColor(sf::Color::White);
  m_algorithm_variants[m_variants_size - 1].setFillColor(sf::Color::Red);
  m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  additional_option(additional);
}

void Visualization_Options::make_lr_button_disappear() {
  if (m_additional_option_index == 0) {
    m_lr_btn_shape[0].setOutlineColor(sf::Color::Black);
    m_triangle_arrow[0].setFillColor(sf::Color::Black);
  } else {
    m_lr_btn_shape[0].setOutlineColor(sf::Color::White);
    m_triangle_arrow[0].setFillColor(sf::Color::Red);
  }
  if (m_additional_option_index == m_additional_option_names.size() - 1) {
    m_lr_btn_shape[1].setOutlineColor(sf::Color::Black);
    m_triangle_arrow[1].setFillColor(sf::Color::Black);
  } else {
    m_lr_btn_shape[1].setOutlineColor(sf::Color::White);
    m_triangle_arrow[1].setFillColor(sf::Color::Red);
  }
}

void Visualization_Options::display_lr_buttons(bool display) {
  if (display) {
    m_lr_btn_shape.resize(2);
    m_triangle_arrow.resize(2);
    make_lr_button_disappear();
    for (int i = 0; i < 2; i++) {
      m_lr_btn_shape[i].setSize({20, 20});
      // m_triangle_arrow[i].setFillColor(sf::Color::Red);
      // m_lr_btn_shape[i].setOutlineColor(sf::Color::White);
      m_lr_btn_shape[i].setFillColor(sf::Color::Black);
      m_lr_btn_shape[i].setOutlineThickness(1.5);
      m_triangle_arrow[i].setPointCount(3);
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

int Visualization_Options::get_additional_option_index() {
  return m_additional_option_index;
}

void Visualization_Options::set_additional_option_index(int value) {
  m_additional_option_index = value;
}

void Visualization_Options::set_setting_selected_algo(
    int selected, std::function<void()> func) {
  m_additional_exists = false;
  m_choosed_algo = selected;
  additional_option(false);
  func();
  m_algorithm_variants[0].setFillColor(sf::Color::White);
  m_algorithm_variants[selected].setFillColor(sf::Color::Green);
}

//TODO:: MAKE ABSTRACT
void Visualization_Options::find_algo(int selected) {
  auto it = m_algo_map.find(std::make_pair(m_asc, selected));
  if (it != m_algo_map.end()) {
    it->second();
  } else {
    std::cerr << "Algorithm not found" << std::endl;
  }
}

//TODO:: MAKE ABSTRACT
void Visualization_Options::find_option(int selected) {
  auto it = m_sort_class_map.find(selected);
  if (it != m_sort_class_map.end()) {
    it->second();
  } else {
    std::cerr << "Option not found" << std::endl;
  }
}

void Visualization_Options::change_option(int selected) {
  if (selected == m_variants_size - 1) {
    m_choosed_algo = 0;
    m_selected_algo_index = 0;
    m_selected_algo_index = 0;
    m_algorithm_variants[0].setFillColor(sf::Color::Green);
    m_algorithm_variants[m_variants_size].setFillColor(sf::Color::Red);
    set_default_options();
    current_screen = visualize;
  } else if (selected > m_variants_size - 1) {
    find_option(selected);
  } else {
    find_algo(selected);
  }
}

void Visualization_Options::set_style(std::vector<std::string> variants,
                                      int pos_y) {
  m_all_options_size = variants.size();
  m_algorithm_variants.resize(m_all_options_size);
  Screen::set_sf_text_style(m_algorithm_variants, variants,
                            m_char_size_text_variants, 50, pos_y, false, true,
                            0, 50);
  m_algorithm_variants[m_variants_size - 1].setFillColor(sf::Color::Red);
  m_algorithm_variants[0].setFillColor(sf::Color::Green);
  int count = 0;
  for (int i = m_variants_size; i < m_all_options_size - c_buttons; i++) {
    m_algorithm_variants[i].setPosition(460, 50 * count + pos_y);
    count++;
  }
  count = 0;
  int temp = 0;
  for (int i = m_all_options_size - c_buttons; i < m_all_options_size; i++) {
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

void Visualization_Options::textbox(int char_size_textbox,
                                    std::size_t number_of_inputs, int pos_y) {
  std::vector<std::string> temp{number_of_inputs};
  for (int i = 0; i < number_of_inputs; i++)
    temp[i] = std::to_string(m_visualization_options[i]);
  Screen::set_sf_text_style(m_textbox_input_style, temp,
                            m_char_size_text_variants, 690, pos_y, false, true,
                            0, 50);
}

void Visualization_Options::typed_on(sf::Event input) {
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

void Visualization_Options::input_box_selected(int item) {
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

void Visualization_Options::visualization_buttons_style(int pos_y) {
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

std::string Visualization_Options::get_display_name() {
  if (auto search = m_display_name.find(
          std::make_pair(m_algorithm_variants[m_choosed_algo].getString(),
                         m_additional_option_index));
      search != m_display_name.end())
    return search->second;
  else
    return "Unknown Algorithm";
}

void Visualization_Options::algo_viz(std::size_t n_elements, int min_val,
                                     int max_val) {
  current_screen = final_visual;
  std::string algo_name;
  if (m_additional_exists == true)
    algo_name = get_display_name();
  else
    algo_name = m_algorithm_variants[m_choosed_algo].getString();
  std::cout << algo_name << '\n';
  final_visual->set_options(n_elements, min_val, max_val, algo_name);
  final_visual->visual();
}

void Visualization_Options::algo_viz(std::size_t n_elements, int min_val,
                                     int max_val, bool bw_case) {}

void Visualization_Options::input_logic(int char_typed) {
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

void Visualization_Options::delete_last_char() {
  std::string t = m_text_input.str();
  std::string newT = "";
  for (int i = 0; i < t.length() - 1; i++) {
    newT += t[i];
  }
  m_text_input.str("");
  m_text_input << newT;
  m_textbox_input_style[m_selected_input_option].setString(m_text_input.str());
  m_temp_value.pop_back();
}
