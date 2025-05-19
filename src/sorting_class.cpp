#include "sorting_class.h"
#include <memory>
#include "visualization.h"

std::shared_ptr<Screen> Sorting_Class::g_dummy_screen = nullptr;

Sorting_Class::Sorting_Class()
    : current_screen(g_dummy_screen),
      visualize(nullptr),
      window_ptr(nullptr),
      final_visual(nullptr),
      m_selected_sort_algo(),
      m_selected_sorting_algo_index(),
      m_choosed_algo(),
      m_sc(),
      m_sort_class_map(),
      m_sort_map(),
      m_algorithm_variants(),
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
      m_triangle_arrow() {}

Sorting_Class::Sorting_Class(std::shared_ptr<Screen>& screen_ptr,
                             std::shared_ptr<Visualizer> viz_ptr,
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
      m_additional_param(false),
      m_additional_exists(true) {

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
  m_additional_option_index = 0;
}

void Sorting_Class::init_visualization_default() {
  final_visual = std::make_unique<Visualization>();
}

void Sorting_Class::init_visualization_sorting() {
  final_visual = std::make_unique<Visualization>(
      current_screen, shared_from_this(), window_ptr);
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
  window.draw(m_additional_option);
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
  m_additional_option.setString("");
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
    m_additional_option.setString(
        m_additional_option_names[m_additional_option_index]);
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

int Sorting_Class::get_additional_option_index() {
  return m_additional_option_index;
}

void Sorting_Class::set_additional_option_index(int value) {
  m_additional_option_index = value;
}

void Sorting_Class::set_selected_sort_variants(
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

void Sorting_Class::set_setting_selected_algo(int selected,
                                              std::function<void()> func) {
  m_additional_exists = false;
  m_choosed_algo = selected;
  set_default_options();
  additional_option(false);
  func();
  m_algorithm_variants[0].setFillColor(sf::Color::White);
  m_algorithm_variants[selected].setFillColor(sf::Color::Green);
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
  m_sort_map[{sort_cat::insertion, 0}] = [this]() {  // INSERTION SORT
    m_additional_exists = true;
    std::vector<std::string> names = {"Normal", "Recursive", "Binary"};
    set_selected_sort_variants(
        0, [this]() { insertion_sort(); }, names, "Variations: ");
  };
  m_sort_map[{sort_cat::insertion, 1}] = [this]() {  // SHELL SORT
    m_additional_exists = true;
    std::vector<std::string> names = {"Original",
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
    set_selected_sort_variants(
        1, [this]() { insertion_sort(); }, names, "Gap: ");
  };
  m_sort_map[{sort_cat::insertion, 2}] = [this]() {  // SPLAYSORT
    set_setting_selected_algo(2, [this]() { insertion_sort(); });
  };
  m_sort_map[{sort_cat::insertion, 3}] = [this]() {  // TREE SORT
    set_setting_selected_algo(3, [this]() { insertion_sort(); });
  };
  m_sort_map[{sort_cat::insertion, 4}] = [this]() {  // LIBRARY SORT
    set_setting_selected_algo(4, [this]() { insertion_sort(); });
  };
  m_sort_map[{sort_cat::insertion, 5}] = [this]() {  // PATIENCE SORT
    set_setting_selected_algo(5, [this]() { insertion_sort(); });
  };
  additional_option(false);
}
void Sorting_Class::initialize_selection() {
  m_sort_map[{sort_cat::selection, 0}] = [this]() {  // SELECTION SORT
    set_setting_selected_algo(0, [this]() { selection_sort(); });
  };
  m_sort_map[{sort_cat::selection, 1}] = [this]() {  // HEAPSORT
    set_setting_selected_algo(1, [this]() { selection_sort(); });
  };
  m_sort_map[{sort_cat::selection, 2}] = [this]() {  //SMOOTH SORT
    set_setting_selected_algo(2, [this]() { selection_sort(); });
  };
  m_sort_map[{sort_cat::selection, 3}] = [this]() {  // CARTESIAN TREE SORT
    set_setting_selected_algo(3, [this]() { selection_sort(); });
  };
  m_sort_map[{sort_cat::selection, 4}] = [this]() {  // TOURNAMENT SORT
    set_setting_selected_algo(4, [this]() { selection_sort(); });
  };
  m_sort_map[{sort_cat::selection, 5}] = [this]() {  // CYCLE SORT
    set_setting_selected_algo(5, [this]() { selection_sort(); });
  };
  m_sort_map[{sort_cat::selection, 6}] = [this]() {  // WEAK-HEAP SORT
    set_setting_selected_algo(6, [this]() { selection_sort(); });
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
    set_setting_selected_algo(1, [this]() { merge_sort(); });
  };
  m_sort_map[{sort_cat::merge, 2}] = [this]() {
    set_setting_selected_algo(2, [this]() { merge_sort(); });
  };
  m_sort_map[{sort_cat::merge, 3}] = [this]() {
    set_setting_selected_algo(3, [this]() { merge_sort(); });
  };
  m_sort_map[{sort_cat::merge, 4}] = [this]() {
    set_setting_selected_algo(4, [this]() { merge_sort(); });
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
    set_setting_selected_algo(1, [this]() { exchange_sort(); });
  };
  m_sort_map[{sort_cat::exchange, 2}] = [this]() {
    set_setting_selected_algo(2, [this]() { exchange_sort(); });
  };
  m_sort_map[{sort_cat::exchange, 3}] = [this]() {
    set_setting_selected_algo(3, [this]() { exchange_sort(); });
  };
  m_sort_map[{sort_cat::exchange, 4}] = [this]() {
    set_setting_selected_algo(4, [this]() { exchange_sort(); });
  };
  m_sort_map[{sort_cat::exchange, 5}] = [this]() {
    set_setting_selected_algo(5, [this]() { exchange_sort(); });
  };
  m_sort_map[{sort_cat::exchange, 6}] = [this]() {
    set_setting_selected_algo(6, [this]() { exchange_sort(); });
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
    set_setting_selected_algo(1, [this]() { distribution_sort(); });
  };
  m_sort_map[{sort_cat::distribution, 2}] = [this]() {
    set_setting_selected_algo(2, [this]() { distribution_sort(); });
  };
  m_sort_map[{sort_cat::distribution, 3}] = [this]() {
    set_setting_selected_algo(3, [this]() { distribution_sort(); });
  };
  m_sort_map[{sort_cat::distribution, 4}] = [this]() {
    set_setting_selected_algo(4, [this]() { distribution_sort(); });
  };
  m_sort_map[{sort_cat::distribution, 5}] = [this]() {
    set_setting_selected_algo(5, [this]() { distribution_sort(); });
  };
  m_sort_map[{sort_cat::distribution, 6}] = [this]() {
    set_setting_selected_algo(6, [this]() { distribution_sort(); });
  };
  m_sort_map[{sort_cat::distribution, 7}] = [this]() {
    set_setting_selected_algo(7, [this]() { distribution_sort(); });
  };
  m_sort_map[{sort_cat::distribution, 8}] = [this]() {
    set_setting_selected_algo(8, [this]() { distribution_sort(); });
  };
  m_sort_map[{sort_cat::distribution, 9}] = [this]() {
    set_setting_selected_algo(9, [this]() { distribution_sort(); });
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
    set_setting_selected_algo(1, [this]() { concurrent_sort(); });
  };
  m_sort_map[{sort_cat::concurrent, 2}] = [this]() {
    set_setting_selected_algo(2, [this]() { concurrent_sort(); });
  };
  m_sort_map[{sort_cat::concurrent, 3}] = [this]() {
    set_setting_selected_algo(3, [this]() { concurrent_sort(); });
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
    current_screen = std::move(visualize);
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
      "Insertion Sort", "Shell Sort",       "Splaysort", "Tree Sort",
      "Library Sort",   "Patience Sorting", "Back"};
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
      "Selection Sort",  "Heapsort",   "Smooth Sort",    "Cartesian Tree Sort",
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
      "Pairwise Sorting Network", "Samplesort", "Back"};
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
        890 + (100 - (m_visualization_buttons_names[i].length() * 35) / 2.0),
        temp + 60 * i + pos_y);
    temp = 100;
  }
}

std::string Sorting_Class::get_display_name() {
  m_display_name[std::make_pair(std::string("Insertion Sort"), 0)] =
      "Insertion Sort";
  m_display_name[std::make_pair(std::string("Insertion Sort"), 1)] =
      "Recursive Insertion Sort";
  m_display_name[std::make_pair(std::string("Insertion Sort"), 2)] =
      "Binary Insertion Sort";
  m_display_name[std::make_pair(std::string("Shell Sort"), 0)] = "Shell Sort";
  m_display_name[std::make_pair(std::string("Shell Sort"), 1)] =
      "Shell Sort Frank & Lazarus";
  m_display_name[std::make_pair(std::string("Shell Sort"), 2)] =
      "Shell Sort Hibbard";
  m_display_name[std::make_pair(std::string("Shell Sort"), 3)] =
      "Shell Sort Papernov & Stasevich";
  m_display_name[std::make_pair(std::string("Shell Sort"), 4)] =
      "Shell Sort Pratt";
  m_display_name[std::make_pair(std::string("Shell Sort"), 5)] =
      "Shell Sort Knuth";
  m_display_name[std::make_pair(std::string("Shell Sort"), 6)] =
      "Shell Sort Incerpi & Sedgewick";
  m_display_name[std::make_pair(std::string("Shell Sort"), 7)] =
      "Shell Sort Sedgewick (1)";
  m_display_name[std::make_pair(std::string("Shell Sort"), 8)] =
      "Shell Sort Sedgewick (2)";
  m_display_name[std::make_pair(std::string("Shell Sort"), 9)] =
      "Shell Sort Gonnet & Baeza-Yates";
  m_display_name[std::make_pair(std::string("Shell Sort"), 10)] =
      "Shell Sort Tokuda";
  m_display_name[std::make_pair(std::string("Shell Sort"), 11)] =
      "Shell Sort Ciura";
  m_display_name[std::make_pair(std::string("Shell Sort"), 12)] =
      "Shell Sort Lee";
  m_display_name[std::make_pair(std::string("Shell Sort"), 13)] =
      "Shell Sort SEJ";
  m_display_name[std::make_pair(std::string("Selection Sort"), 0)] =
      "Selection Sort";
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

void Sorting_Class::algo_viz(std::size_t n_elements, int min_val, int max_val) {
  current_screen = std::move(final_visual);
  std::string algo_name;
  if (m_additional_exists == true)
    algo_name = get_display_name();
  else
    algo_name = m_algorithm_variants[m_choosed_algo].getString();
  std::cout << algo_name << '\n';
  final_visual->set_options(n_elements, min_val, max_val, algo_name);
  final_visual->visual();
}

void Sorting_Class::algo_viz(std::size_t n_elements, int min_val, int max_val,
                             bool bw_case) {}
