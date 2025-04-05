#include "sorting_class.h"
#include <SFML/Graphics/PrimitiveType.hpp>
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
      m_option_size(3),
      m_additional_param(false) {

  final_visual = new Visualization(screen_ptr, this, window_ptr);
  //INITIALIZE VISUALIZATION BUTTONS
  m_visualization_buttons_names = {"Start", "Example", "Worst case",
                                   "Best Case"};
  visualization_buttons_style(150);
  // INITALIZE VISUALIZATION OPTIONS VECTOR WITH VALUES:
  // NUMBER OF ELEMENTS = 10, MINIMUM RANGE OF ELEMENTS = 0, MAXIMUM RANGE OF ELEMENTS = 100
  m_visualization_options_names = {
      "Number of elemenst:", "Minimum value:", "Maximum value:"};
  m_visualization_options = {10, 0, 100};
  textbox(20, 3, 150);
  m_choosed_algo = 0;
  m_lr_btn_shape.resize(0);
  m_triangle_arrow.resize(0);
  m_gaps_index = 0;
  m_gaps_seq_names = {"Original",
                      "Frank & Lazarus",
                      "Hibbard",
                      "Papernov & Stasevich",
                      "Pratt",
                      "Knuth",
                      "Incerpi & Sedgewick",
                      "Sedgewick 1",
                      "Sedgewick 2",
                      "Gonnt & Baeza-Yates",
                      "Tokuda",
                      "Ciura",
                      "Lee",
                      "S & E & J"};
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
  for (const auto& x : m_lr_btn_shape)
    window.draw(x);
  for (const auto& x : m_triangle_arrow)
    window.draw(x);
  window.draw(m_gaps_seq);
}

void Sorting_Class::move_up() {
  if (!m_possible_input && !m_additional_param) {
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
  if (!m_possible_input && !m_additional_param) {
    if (m_selected_sorting_algo_index + 1 <
        m_option_size + m_variants_size + c_buttons) {
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
  if (!m_possible_input) {
    if (m_additional_param) {
      if (m_gaps_index > 0) {
        m_gaps_index--;
        float text_width = m_gaps_seq_names[m_gaps_index].length() * 5;
        float min_x = 630;
        float max_x = 780;
        float center_x = (min_x + max_x) / 2;
        m_gaps_seq.setPosition(center_x - text_width / 2, 310);
        m_gaps_seq.setString(m_gaps_seq_names[m_gaps_index]);
      }
    } else {
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
            m_selected_sorting_algo_index <=
                m_algorithm_variants.size() - c_buttons - 1) {
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
}

void Sorting_Class::move_right() {
  if (!m_possible_input) {
    if (m_additional_param) {
      if (m_gaps_index < m_gaps_seq_names.size() - 1) {
        m_gaps_index++;
        float text_width = m_gaps_seq_names[m_gaps_index].length() * 5;
        float min_x = 630;
        float max_x = 780;
        float center_x = (min_x + max_x) / 2;
        m_gaps_seq.setPosition(center_x - text_width / 2, 310);
        m_gaps_seq.setString(m_gaps_seq_names[m_gaps_index]);
      }
    } else {
      if (!(m_selected_sorting_algo_index >=
            m_algorithm_variants.size() - c_buttons)) {
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
        if (m_selected_sorting_algo_index <
                m_algorithm_variants.size() - c_buttons &&
            !(m_selected_sorting_algo_index >= m_variants_size)) {
          m_selected_sorting_algo_index = m_variants_size;
          m_selected_sort_algo = m_selected_sorting_algo_index;
          m_algorithm_variants[m_selected_sort_algo].setFillColor(
              sf::Color::Green);
        } else if (m_selected_sorting_algo_index <
                   m_algorithm_variants.size() - c_buttons) {
          m_selected_sorting_algo_index =
              m_algorithm_variants.size() - c_buttons;
          m_selected_sort_algo = m_selected_sorting_algo_index;
          m_algorithm_variants[m_selected_sort_algo].setFillColor(
              sf::Color::Green);
        }
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

void Sorting_Class::set_default_options() {
  m_option_size = 3;
  m_visualization_options_names.resize(m_option_size);
  m_visualization_options_names = {
      "Number of elemenst:", "Minimum value:", "Maximum value:"};
}

void Sorting_Class::additional_option(bool additional) {
  m_gaps_seq.setString("");
  display_lr_buttons(false);
  m_sort_class_map[m_variants_size] = [this]() {
    input_box_selected(0);
  };
  m_sort_class_map[m_variants_size + 1] = [this]() {
    input_box_selected(1);
  };
  m_sort_class_map[m_variants_size + 2] = [this]() {
    input_box_selected(2);
  };
  int i = (additional) ? 1 : 0;
  if (additional) {
    m_gaps_seq.setString(m_gaps_seq_names[m_gaps_index]);
    m_sort_class_map[m_variants_size + 3] = [this]() {
      if (m_additional_param) {
        m_additional_param = false;
        display_lr_buttons(false);
      } else {
        display_lr_buttons(true);
        m_additional_param = true;
      }
    };
  }
  m_sort_class_map[m_variants_size + 3 + i] = [this]() {
    algo_viz(m_visualization_options[0], m_visualization_options[1],
             m_visualization_options[2]);
  };
  m_sort_class_map[m_variants_size + 4 + i] = [this]() {
    algo_viz(10, 0, 10);
  };
  m_sort_class_map[m_variants_size + 5 + i] = [this]() {
    algo_viz(100, 0, 100, false);
  };
  m_sort_class_map[m_variants_size + 6 + i] = [this]() {
    algo_viz(100, 0, 100, true);
  };
}

void Sorting_Class::display_lr_buttons(bool display) {
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

int Sorting_Class::get_shell_gap() {
  return m_gaps_index;
}

void Sorting_Class::set_shell_sort(int selected) {
  m_choosed_algo = 2;
  m_option_size = 4;
  m_visualization_options_names.resize(m_option_size);
  m_visualization_options_names[3] = "Gap sequence: ";
  insertion_sort();
  for (auto& x : m_algorithm_variants)
    x.setFillColor(sf::Color::White);
  m_algorithm_variants[m_variants_size - 1].setFillColor(sf::Color::Red);
  m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  additional_option(true);
  m_gaps_seq.setFont(m_open_sans);
  m_gaps_seq.setFillColor(sf::Color::White);
  m_gaps_seq.setCharacterSize(10);
  m_gaps_seq.setStyle(sf::Text::Bold);
  float text_width = m_gaps_seq_names[m_gaps_index].length() * 5;
  float min_x = 630;
  float max_x = 780;
  float center_x = (min_x + max_x) / 2;
  m_gaps_seq.setPosition(center_x - text_width / 2, 310);
  m_gaps_seq.setString(m_gaps_seq_names[m_gaps_index]);
}

void Sorting_Class::initalize_sorting_algos() {
  initialize_insertion();
  initialize_selection();
  initialize_merge();
  initialize_exchange();
  initialize_distribution();
  initialize_concurrent();
}

void Sorting_Class::initialize_insertion() {
  m_sort_map[{sort_cat::insertion, 0}] = [this]() {
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    insertion_sort();
  };
  m_sort_map[{sort_cat::insertion, 1}] = [this]() {
    m_choosed_algo = 1;
    set_default_options();
    additional_option(false);
    insertion_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[1].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::insertion, 2}] = [this]() {
    set_shell_sort(2);
  };
  m_sort_map[{sort_cat::insertion, 3}] = [this]() {
    m_choosed_algo = 3;
    set_default_options();
    additional_option(false);
    insertion_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[3].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::insertion, 4}] = [this]() {
    m_choosed_algo = 4;
    set_default_options();
    additional_option(false);
    insertion_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[4].setFillColor(sf::Color::Green);
  };
  additional_option(false);
}
void Sorting_Class::initialize_selection() {
  m_sort_map[{sort_cat::selection, 0}] = [this]() {
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    selection_sort();
  };
  m_sort_map[{sort_cat::selection, 1}] = [this]() {
    m_choosed_algo = 1;
    set_default_options();
    additional_option(false);
    selection_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[1].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::selection, 2}] = [this]() {
    m_choosed_algo = 2;
    set_default_options();
    additional_option(false);
    selection_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[2].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::selection, 3}] = [this]() {
    m_choosed_algo = 3;
    set_default_options();
    additional_option(false);
    selection_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[3].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::selection, 4}] = [this]() {
    m_choosed_algo = 4;
    set_default_options();
    additional_option(false);
    selection_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[4].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::selection, 5}] = [this]() {
    m_choosed_algo = 5;
    set_default_options();
    additional_option(false);
    selection_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[5].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::selection, 6}] = [this]() {
    m_choosed_algo = 6;
    set_default_options();
    additional_option(false);
    selection_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[6].setFillColor(sf::Color::Green);
  };
  additional_option(false);
}
void Sorting_Class::initialize_merge() {
  m_sort_map[{sort_cat::merge, 0}] = [this]() {
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    merge_sort();
  };
  m_sort_map[{sort_cat::merge, 1}] = [this]() {
    m_choosed_algo = 1;
    set_default_options();
    additional_option(false);
    merge_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[1].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::merge, 2}] = [this]() {
    m_choosed_algo = 2;
    set_default_options();
    additional_option(false);
    merge_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[2].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::merge, 3}] = [this]() {
    m_choosed_algo = 3;
    set_default_options();
    additional_option(false);
    merge_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[3].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::merge, 4}] = [this]() {
    m_choosed_algo = 4;
    set_default_options();
    additional_option(false);
    merge_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[4].setFillColor(sf::Color::Green);
  };
  additional_option(false);
}
void Sorting_Class::initialize_exchange() {
  m_sort_map[{sort_cat::exchange, 0}] = [this]() {
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    exchange_sort();
  };
  m_sort_map[{sort_cat::exchange, 1}] = [this]() {
    m_choosed_algo = 1;
    set_default_options();
    additional_option(false);
    exchange_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[1].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::exchange, 2}] = [this]() {
    m_choosed_algo = 2;
    set_default_options();
    additional_option(false);
    exchange_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[2].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::exchange, 3}] = [this]() {
    m_choosed_algo = 3;
    set_default_options();
    additional_option(false);
    exchange_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[3].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::exchange, 4}] = [this]() {
    m_choosed_algo = 4;
    set_default_options();
    additional_option(false);
    exchange_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[4].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::exchange, 5}] = [this]() {
    m_choosed_algo = 5;
    set_default_options();
    additional_option(false);
    exchange_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[5].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::exchange, 6}] = [this]() {
    m_choosed_algo = 6;
    set_default_options();
    additional_option(false);
    exchange_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[6].setFillColor(sf::Color::Green);
  };
  additional_option(false);
}
void Sorting_Class::initialize_distribution() {
  m_sort_map[{sort_cat::distribution, 0}] = [this]() {
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    distribution_sort();
  };
  m_sort_map[{sort_cat::distribution, 1}] = [this]() {
    m_choosed_algo = 1;
    set_default_options();
    additional_option(false);
    distribution_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::distribution, 2}] = [this]() {
    m_choosed_algo = 2;
    set_default_options();
    additional_option(false);
    distribution_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::distribution, 3}] = [this]() {
    m_choosed_algo = 3;
    set_default_options();
    additional_option(false);
    distribution_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::distribution, 4}] = [this]() {
    m_choosed_algo = 4;
    set_default_options();
    additional_option(false);
    distribution_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::distribution, 5}] = [this]() {
    m_choosed_algo = 5;
    set_default_options();
    additional_option(false);
    distribution_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::distribution, 6}] = [this]() {
    m_choosed_algo = 6;
    set_default_options();
    additional_option(false);
    distribution_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::distribution, 7}] = [this]() {
    m_choosed_algo = 7;
    set_default_options();
    additional_option(false);
    distribution_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::distribution, 8}] = [this]() {
    m_choosed_algo = 8;
    set_default_options();
    additional_option(false);
    distribution_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::distribution, 9}] = [this]() {
    m_choosed_algo = 9;
    set_default_options();
    additional_option(false);
    distribution_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[m_choosed_algo].setFillColor(sf::Color::Green);
  };
  additional_option(false);
}
void Sorting_Class::initialize_concurrent() {
  m_sort_map[{sort_cat::concurrent, 0}] = [this]() {
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    concurrent_sort();
  };
  m_sort_map[{sort_cat::concurrent, 1}] = [this]() {
    m_choosed_algo = 1;
    set_default_options();
    additional_option(false);
    concurrent_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[1].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::concurrent, 2}] = [this]() {
    m_choosed_algo = 2;
    set_default_options();
    additional_option(false);
    concurrent_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[2].setFillColor(sf::Color::Green);
  };
  m_sort_map[{sort_cat::concurrent, 3}] = [this]() {
    m_choosed_algo = 3;
    set_default_options();
    additional_option(false);
    concurrent_sort();
    m_algorithm_variants[0].setFillColor(sf::Color::White);
    m_algorithm_variants[3].setFillColor(sf::Color::Green);
  };
  additional_option(false);
}

void Sorting_Class::find_algo(int selected) {
  auto it = m_sort_map.find(std::make_pair(m_sc, selected));
  if (it != m_sort_map.end()) {
    it->second();
  } else {
    std::cerr << "Algorithm not found" << std::endl;
  }
}

void Sorting_Class::find_option(int selected) {
  auto it = m_sort_class_map.find(selected);
  if (it != m_sort_class_map.end()) {
    it->second();
  } else {
    std::cerr << "Option not found" << std::endl;
  }
}

void Sorting_Class::change_option(int selected) {
  if (selected == m_variants_size - 1) {
    m_choosed_algo = 0;
    m_selected_sort_algo = 0;
    m_selected_sorting_algo_index = 0;
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

void Sorting_Class::set_style(std::vector<std::string> variants, int pos_y) {
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

void Sorting_Class::insertion_sort() {
  std::vector<std::string> insertion_sort_variants = {
      "Insertion Sort", "Recursive Insertion Sort",
      "Shell Sort",     "Binary Insertion Sort",
      "Library Sort",   "Back"};
  m_variants_size = insertion_sort_variants.size();
  insertion_sort_variants.insert(insertion_sort_variants.end(),
                                 m_visualization_options_names.begin(),
                                 m_visualization_options_names.end());
  insertion_sort_variants.insert(insertion_sort_variants.end(),
                                 m_visualization_buttons_names.begin(),
                                 m_visualization_buttons_names.end());
  set_style(insertion_sort_variants, 150);
  m_sc = sort_cat::insertion;
}

void Sorting_Class::selection_sort() {
  std::vector<std::string> selection_sort_variants = {
      "Selection Sort",  "Heapsort",   "Smoothsort",     "Cartesian Tree Sort",
      "Tournament Sort", "Cycle Sort", "Weak-Heap Sort", "Back"};
  m_variants_size = selection_sort_variants.size();
  selection_sort_variants.insert(selection_sort_variants.end(),
                                 m_visualization_options_names.begin(),
                                 m_visualization_options_names.end());
  selection_sort_variants.insert(selection_sort_variants.end(),
                                 m_visualization_buttons_names.begin(),
                                 m_visualization_buttons_names.end());
  set_style(selection_sort_variants, 150);
  m_sc = sort_cat::selection;
}

void Sorting_Class::merge_sort() {
  std::vector<std::string> merge_sort_variants = {
      "Merge Sort", "Cascade Merge Sort", "Oscillating Merge Sort",
      "Polyphase Merge Sort", "Back"};
  m_variants_size = merge_sort_variants.size();
  merge_sort_variants.insert(merge_sort_variants.end(),
                             m_visualization_options_names.begin(),
                             m_visualization_options_names.end());
  merge_sort_variants.insert(merge_sort_variants.end(),
                             m_visualization_buttons_names.begin(),
                             m_visualization_buttons_names.end());
  set_style(merge_sort_variants, 150);
  m_sc = sort_cat::merge;
}

void Sorting_Class::exchange_sort() {
  std::vector<std::string> exchange_sort_variants = {
      "Bubble Sort", "Cocktail Sort",          "Odd-Even Sort", "Comb Sort",
      "Gnome Sort",  "Proportion Extend Sort", "Quicksort",     "Back"};
  m_variants_size = exchange_sort_variants.size();
  exchange_sort_variants.insert(exchange_sort_variants.end(),
                                m_visualization_options_names.begin(),
                                m_visualization_options_names.end());
  exchange_sort_variants.insert(exchange_sort_variants.end(),
                                m_visualization_buttons_names.begin(),
                                m_visualization_buttons_names.end());
  set_style(exchange_sort_variants, 150);
  m_sc = sort_cat::exchange;
}

void Sorting_Class::distribution_sort() {
  std::vector<std::string> distribution_sort_variants = {
      "American Flag Sort", "Bead Sort",     "Bucket Sort",
      "Burstsort",          "Counting Sort", "Interpolation Sort",
      "Pigeonhole Sort",    "Proxmap Sort",  "Radix Sort",
      "Flashsort",          "Back"};
  m_variants_size = distribution_sort_variants.size();
  distribution_sort_variants.insert(distribution_sort_variants.end(),
                                    m_visualization_options_names.begin(),
                                    m_visualization_options_names.end());
  distribution_sort_variants.insert(distribution_sort_variants.end(),
                                    m_visualization_buttons_names.begin(),
                                    m_visualization_buttons_names.end());
  set_style(distribution_sort_variants, 150);
  m_sc = sort_cat::distribution;
}

void Sorting_Class::concurrent_sort() {
  std::vector<std::string> concurrent_sort_variants = {
      "Bitonic Sorter", "Batcher Odd-Even Mergesort",
      "Pairwise Sorting Netowrk", "Samplesort", "Back"};
  m_variants_size = concurrent_sort_variants.size();
  concurrent_sort_variants.insert(concurrent_sort_variants.end(),
                                  m_visualization_options_names.begin(),
                                  m_visualization_options_names.end());
  concurrent_sort_variants.insert(concurrent_sort_variants.end(),
                                  m_visualization_buttons_names.begin(),
                                  m_visualization_buttons_names.end());
  set_style(concurrent_sort_variants, 150);
  m_sc = sort_cat::concurrent;
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
