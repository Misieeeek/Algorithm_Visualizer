#include "visualizer.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include "main_menu.h"
#include "main_window.h"

Visualizer::Visualizer(Screen** screen_ptr, Screen* menu)
    : m_selected_algorithm_index(0),
      m_selected_algorithm(0),
      m_category_option(true),
      m_category_font_size(35),
      m_drop_down_item_font_size(20) {

  current_screen = screen_ptr;
  main_menu = menu;
  sort_class = new Sorting_Class(screen_ptr, this);
  std::array<std::string, c_num_algos> algo = {
      "Sorting Algorithms", "Searching Algorithms",
      "Data Structures",    "Dynamic Programming",
      "Greedy Algorithms",  "Advanced Data Structures",
      "Graph Algorithms",   "Back"};

  Screen::set_sf_text_style(m_list_algorithms, algo, m_category_font_size, 50,
                            150, false, true, 0, 50);
  m_list_algorithms[c_num_algos - 1].setFillColor(sf::Color::Red);
  m_list_algorithms[0].setFillColor(sf::Color::Green);
  m_dropped = false;
  // SETTING NAMES FOR DIFFERENT ALGO CATEGORIES
  m_algo_sort = {"Insertion Sort", "Selection Sort", "Merge Sort",
                 "Bubble Sort",    "Heap Sort",      "Quick Sort"};
  m_algo_search = {"Linear Search", "Binary Search"};
  m_algo_ds = {"Stack",
               "Queue",
               "Linked List",
               "Hash Table",
               "Binary Search Tree",
               "Red-Black Tree",
               "AVL Tree",
               "Treaps"};
  m_algo_dynamic = {"Cut Rod", "Cut Rod (Memoization)", "Cut Rod (Tabulation)",
                    "Longest Common Subsequence"};
  m_algo_greedy = {"Huffman Coding", "Activity Selector"};
  m_algo_advancedds = {"B-Tree", "Fibonacci Heap", "Van Emde Boas Tree"};
  m_algo_graph = {"1", "2", "3"};
  // INITIALIZE MAP FOR ALGORITHMS
  initialize_algorithms();
}

Visualizer::~Visualizer() {
  delete sort_class;
}

void Visualizer::move_up() {
  if (m_dropped || !m_category_option) {
    if (m_dropped_items_index - 1 >= 0) {
      m_list_algo[m_dropped_items_index].setFillColor(sf::Color::White);
      m_dropped_items_index--;
      m_list_algo[m_dropped_items_index].setFillColor(sf::Color::Green);
      m_dropped_items = m_dropped_items_index;
    } else {
      m_category_option = true;
      m_list_algo[m_dropped_items_index].setFillColor(sf::Color::White);
      m_list_algorithms[m_selected_algorithm_index].setFillColor(
          sf::Color::Green);
    }
  } else {
    if (m_selected_algorithm_index - 1 >= 0) {
      if (m_selected_algorithm_index == c_num_algos - 1)
        m_list_algorithms[m_selected_algorithm_index].setFillColor(
            sf::Color::Red);
      else
        m_list_algorithms[m_selected_algorithm_index].setFillColor(
            sf::Color::White);
      m_selected_algorithm_index--;
      m_list_algorithms[m_selected_algorithm_index].setFillColor(
          sf::Color::Green);
      m_selected_algorithm = m_selected_algorithm_index;
    }
  }
}

void Visualizer::move_down() {
  if (m_dropped) {
    if (m_dropped_items_index + 1 < m_list_algo.size()) {
      if (m_category_option) {
        m_category_option = false;
        m_list_algo[0].setFillColor(sf::Color::Green);
        m_list_algorithms[m_selected_algorithm_index].setFillColor(
            sf::Color::White);
      } else {
        m_list_algo[m_dropped_items_index].setFillColor(sf::Color::White);
        m_dropped_items_index++;
        m_list_algo[m_dropped_items_index].setFillColor(sf::Color::Green);
        m_dropped_items = m_dropped_items_index;
      }
    }
  } else {
    if (m_selected_algorithm_index + 1 < c_num_algos) {
      m_list_algorithms[m_selected_algorithm_index].setFillColor(
          sf::Color::White);
      m_selected_algorithm_index++;
      m_list_algorithms[m_selected_algorithm_index].setFillColor(
          sf::Color::Green);
      m_selected_algorithm = m_selected_algorithm_index;
    }
  }
}

void Visualizer::draw(sf::RenderWindow& window) {
  m_opend = true;
  if (static_cast<int>(m_ac) >= 0 && static_cast<int>(m_ac) < 7) {
    for (const auto& x : m_list_algo)
      window.draw(x);
    for (const auto& x : m_list_algorithms)
      window.draw(x);
  } else {
    for (int i = 0; i < c_num_algos; i++) {
      m_list_algorithms[i].setPosition(50, 50 * i + 150);
      window.draw(m_list_algorithms[i]);
    }
  }
}

void Visualizer::change_option(int selected) {
  if (!m_dropped) {       // Place where drop down menu is deactivated
    if (selected == 7) {  // EXIT out of visualizer
      m_opend = false;
      m_selected_algorithm = 0;
      m_selected_algorithm_index = 0;
      m_list_algorithms[0].setFillColor(sf::Color::Green);
      m_list_algorithms[c_num_algos - 1].setFillColor(sf::Color::Red);
      m_dropped = true;
      *current_screen = main_menu;
    } else {          // Every other option than EXIT
      if (m_opend) {  // Prevents activating drop down menu comming from main menu
        m_dropped = true;
        m_dropped_items = 0;
        m_dropped_items_index = 0;
        drop_down(selected);
      } else {
        drop_down(7);
        m_dropped = false;
      }
    }
  } else {                    // Place where drop down menu is active
    if (m_category_option) {  // currently standing at algorithm category
      m_dropped = false;
      drop_down(7);
    } else {  // Place where drop down menus options are executed
      go_to_algo_screen(selected);
    }
  }
}

void Visualizer::drop_down(int option) {
  switch (option) {
    case 0:
      m_ac = algo_cat::sorting;
      general_algo_list(c_num_sort, m_algo_sort, 1, 100, 50, 260);
      break;
    case 1:
      m_ac = algo_cat::searching;
      general_algo_list(c_num_search, m_algo_search, 2, 250, 150, 220);
      break;
    case 2:
      m_ac = algo_cat::ds;
      general_algo_list(c_num_ds, m_algo_ds, 3, 200, 50, 320);
      break;
    case 3:
      m_ac = algo_cat::dynamic;
      general_algo_list(c_num_dynamic, m_algo_dynamic, 4, 300, 100, 230);
      break;
    case 4:
      m_ac = algo_cat::greedy;
      general_algo_list(c_num_greedy, m_algo_greedy, 5, 390, 140, 210);
      break;
    case 5:
      m_ac = algo_cat::advancedds;
      general_algo_list(c_num_advancedds, m_algo_advancedds, 6, 400, 100, 210);
      break;
    case 6:
      m_ac = algo_cat::graph;
      general_algo_list(c_num_graph, m_algo_graph, 7, 445, 100, 185);
      break;
    case 7:
      m_ac = algo_cat::none;
      break;
  }
}

void Visualizer::general_algo_list(std::size_t number_of_categories,
                                   std::span<std::string> list_of_algo,
                                   int end_iter, int add_val_pos_x_drop_down,
                                   int add_val_pos_x_categories_before,
                                   int add_val_pos_x_categories_after) {
  m_list_algo.resize(number_of_categories);
  Screen::set_sf_text_style(m_list_algo, list_of_algo,
                            m_drop_down_item_font_size, 100,
                            add_val_pos_x_drop_down, false, true, 0, 35);

  for (int i = 0; i < static_cast<int>(c_num_algos); i++) {
    if (!(i >= end_iter))
      m_list_algorithms[i].setPosition(
          50, 50 * i + add_val_pos_x_categories_before);
    else
      m_list_algorithms[i].setPosition(50,
                                       50 * i + add_val_pos_x_categories_after);
  }
}

int Visualizer::pressed() {
  if (m_category_option)
    return m_selected_algorithm;
  else
    return m_dropped_items;
}

void Visualizer::initialize_sorting() {
  algorithm_map[{algo_cat::sorting, 0}] = [this]() {
    *current_screen = sort_class;
    sort_class->insertion_sort();
  };
  algorithm_map[{algo_cat::sorting, 1}] = []() {
    std::cout << "Selection --------------------Sort\n";
  };
  algorithm_map[{algo_cat::sorting, 2}] = []() {
    std::cout << "Merge Sort\n";
  };
  algorithm_map[{algo_cat::sorting, 3}] = []() {
    std::cout << "Bubble Sort\n";
  };
  algorithm_map[{algo_cat::sorting, 4}] = []() {
    std::cout << "Heap Sort\n";
  };
  algorithm_map[{algo_cat::sorting, 5}] = []() {
    std::cout << "Quick Sort\n";
  };
}
void Visualizer::initialize_searching() {
  algorithm_map[{algo_cat::searching, 0}] = []() {
    std::cout << "Linear Search\n";
  };
  algorithm_map[{algo_cat::searching, 1}] = []() {
    std::cout << "Binary Search\n";
  };
}

void Visualizer::initialize_ds() {
  algorithm_map[{algo_cat::ds, 0}] = []() {
    std::cout << "Stack\n";
  };
  algorithm_map[{algo_cat::ds, 1}] = []() {
    std::cout << "Queue\n";
  };
  algorithm_map[{algo_cat::ds, 2}] = []() {
    std::cout << "Linked List\n";
  };
  algorithm_map[{algo_cat::ds, 3}] = []() {
    std::cout << "Hash Table\n";
  };
  algorithm_map[{algo_cat::ds, 4}] = []() {
    std::cout << "Binary Search Tree\n";
  };
  algorithm_map[{algo_cat::ds, 5}] = []() {
    std::cout << "Red-Black Tree\n";
  };
  algorithm_map[{algo_cat::ds, 6}] = []() {
    std::cout << "AVL Tree\n";
  };
  algorithm_map[{algo_cat::ds, 7}] = []() {
    std::cout << "Treaps\n";
  };
}

void Visualizer::initialize_dynamic() {
  algorithm_map[{algo_cat::dynamic, 0}] = []() {
    std::cout << "Cut Rod\n";
  };
  algorithm_map[{algo_cat::dynamic, 1}] = []() {
    std::cout << "Cut Rod (Memo)\n";
  };
  algorithm_map[{algo_cat::dynamic, 2}] = []() {
    std::cout << "Cut Rod (Tab)\n";
  };
  algorithm_map[{algo_cat::dynamic, 3}] = []() {
    std::cout << "Longest Common Subsequence\n";
  };
}

void Visualizer::initialize_greedy() {
  algorithm_map[{algo_cat::greedy, 0}] = []() {
    std::cout << "Huffman Codign\n";
  };
  algorithm_map[{algo_cat::greedy, 1}] = []() {
    std::cout << "Activity Selector\n";
  };
}

void Visualizer::initialize_advancedds() {
  algorithm_map[{algo_cat::advancedds, 0}] = []() {
    std::cout << "B-Tree\n";
  };
  algorithm_map[{algo_cat::advancedds, 1}] = []() {
    std::cout << "Fibonacci Tree\n";
  };
  algorithm_map[{algo_cat::advancedds, 2}] = []() {
    std::cout << "Van Emde Boas Tree\n";
  };
}

void Visualizer::initialize_graph() {
  algorithm_map[{algo_cat::graph, 0}] = []() {
    std::cout << "1\n";
  };
  algorithm_map[{algo_cat::graph, 1}] = []() {
    std::cout << "2\n";
  };
  algorithm_map[{algo_cat::graph, 2}] = []() {
    std::cout << "3\n";
  };
}

void Visualizer::initialize_algorithms() {
  initialize_sorting();
  initialize_searching();
  initialize_ds();
  initialize_dynamic();
  initialize_greedy();
  initialize_advancedds();
  initialize_graph();
}

void Visualizer::go_to_algo_screen(int selected) {
  auto it = algorithm_map.find(std::make_pair(m_ac, selected));
  if (it != algorithm_map.end()) {
    it->second();  // ALGORITHM STYLES
  } else {
    std::cerr << "Algorithm not found" << std::endl;
  }
}

//------------------------------------------------------- Sorting
Sorting_Class::Sorting_Class(Screen** screen_ptr, Visualizer* viz_ptr)
    : current_screen(screen_ptr),
      visualize(viz_ptr),
      m_selected_sort_algo(0),
      m_selected_sorting_algo_index(0),
      m_char_size_text_variants(20),
      m_possible_input(false),
      m_temp_value("") {

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

Sorting_Class::~Sorting_Class() {}

void Sorting_Class::draw(sf::RenderWindow& window) {
  for (const auto& x : m_visualization_buttons_shape)
    window.draw(x);
  for (const auto& x : m_algorithm_variants)
    window.draw(x);
  for (const auto& x : m_headers)
    window.draw(x);
  for (const auto& x : m_textbox_input_style)
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
  if (!m_possible_input) {
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
  if (!m_possible_input) {
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

void Sorting_Class::change_option(int selected) {
  switch (selected) {
    case 0:
      m_choosed_algo = 0;
      std::cout << "INSERTION SORT\n";
      break;
    case 1:
      m_choosed_algo = 1;
      std::cout << "Recursive Insertion Sort\n";
      break;
    case 2:
      m_choosed_algo = 2;
      std::cout << "Shell Sort\n";
      break;
    case 3:
      m_choosed_algo = 3;
      std::cout << "Binary Insertion Sort\n";
      break;
    case 4:
      m_choosed_algo = 4;
      std::cout << "Library Sort\n";
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
      std::cout << "Start\n";
      break;
    case 10:
      std::cout << "Example\n";
      break;
    case 11:
      std::cout << "Worst\n";
      break;
    case 12:
      std::cout << "Best\n";
      break;
  }
}

void Sorting_Class::drop_down(int option) {}

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
