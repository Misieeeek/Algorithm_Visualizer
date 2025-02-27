#include "visualizer.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include "main_menu.h"
#include "main_window.h"

std::map<std::pair<Algocat, int>, std::function<void()>,
         algocat_pair_comparator>
    algorithm_map;

Visualizer::Visualizer(Screen** screen_ptr, Screen* menu)
    : m_selected_algorithm_index(0),
      m_selected_algorithm(0),
      m_category_option(true),
      m_category_font_size(35),
      m_drop_down_item_font_size(20) {

  std::filesystem::current_path(
      std::filesystem::path(__FILE__).parent_path().parent_path());

  if (!m_open_sans.loadFromFile("assets/fonts/OpenSans-Regular.ttf")) {
    std::cerr << "Failed to load font" << std::endl;
  }

  current_screen = screen_ptr;
  main_menu = menu;
  sort_class = new Sorting_Class(screen_ptr, this);
  std::string algo[] = {"Sorting Algorithms", "Searching Algorithms",
                        "Data Structures",    "Dynamic Programming",
                        "Greedy Algorithms",  "Advanced Data Structures",
                        "Graph Algorithms",   "Back"};

  for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++) {
    m_list_algorithms[i].setFont(m_open_sans);
    m_list_algorithms[i].setFillColor(sf::Color::White);
    m_list_algorithms[i].setCharacterSize(m_category_font_size);
    m_list_algorithms[i].setStyle(sf::Text::Bold);
    m_list_algorithms[i].setPosition(50, 50 * i + 150);
    m_list_algorithms[i].setString(algo[i]);
  }
  m_list_algorithms[NUMBER_OF_ALGORITHMS - 1].setFillColor(sf::Color::Red);
  m_list_algorithms[0].setFillColor(sf::Color::Green);
  m_dropped = false;

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
      if (m_selected_algorithm_index == NUMBER_OF_ALGORITHMS - 1)
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
    if (m_selected_algorithm_index + 1 < NUMBER_OF_ALGORITHMS) {
      m_list_algorithms[m_selected_algorithm_index].setFillColor(
          sf::Color::White);
      m_selected_algorithm_index++;
      m_list_algorithms[m_selected_algorithm_index].setFillColor(
          sf::Color::Green);
      m_selected_algorithm = m_selected_algorithm_index;
    }
  }
}

void Visualizer::move_left() {}
void Visualizer::move_right() {}

void Visualizer::draw(sf::RenderWindow& window) {
  m_opend = true;
  if (static_cast<int>(m_ac) >= 0 && static_cast<int>(m_ac) < 7) {
    for (int i = 0; i < m_list_algo.size(); i++)
      window.draw(m_list_algo[i]);
    for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(m_list_algorithms[i]);
  } else {
    for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++) {
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
      m_list_algorithms[NUMBER_OF_ALGORITHMS - 1].setFillColor(sf::Color::Red);
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
      m_ac = Algocat::SORTING;
      general_algo_list(NUMBER_OF_SORT_ALGO, m_algo_sort, 1, 100, 50, 260);
      break;
    case 1:
      m_ac = Algocat::SEARCHING;
      general_algo_list(NUMBER_OF_SEARCH_ALGO, m_algo_search, 2, 250, 150, 220);
      break;
    case 2:
      m_ac = Algocat::DS;
      general_algo_list(NUMBER_OF_DS_ALGO, m_algo_ds, 3, 200, 50, 320);
      break;
    case 3:
      m_ac = Algocat::DYNAMIC;
      general_algo_list(NUMBER_OF_DYNAMIC_ALGO, m_algo_dynamic, 4, 300, 100,
                        230);
      break;
    case 4:
      m_ac = Algocat::GREEDY;
      general_algo_list(NUMBER_OF_GREEDY_ALGO, m_algo_greedy, 5, 390, 140, 210);
      break;
    case 5:
      m_ac = Algocat::ADVANCEDDS;
      general_algo_list(NUMBER_OF_ADVANCEDDS_ALGO, m_algo_advancedds, 6, 400,
                        100, 210);
      break;
    case 6:
      m_ac = Algocat::GRAPH;
      general_algo_list(NUMBER_OF_GRAPH_ALGO, m_algo_graph, 7, 445, 100, 185);
      break;
    case 7:
      m_ac = Algocat::NONE;
      break;
  }
}

void Visualizer::general_algo_list(int number_of_categories,
                                   std::vector<std::string> list_of_algo,
                                   int end_iter, int add_val_pos_x_drop_down,
                                   int add_val_pos_x_categories_before,
                                   int add_val_pos_x_categories_after) {
  m_list_algo.resize(number_of_categories);
  for (int i = 0; i < number_of_categories; i++) {
    m_list_algo[i].setFont(m_open_sans);
    m_list_algo[i].setFillColor(sf::Color::White);
    m_list_algo[i].setCharacterSize(m_drop_down_item_font_size);
    m_list_algo[i].setStyle(sf::Text::Bold);
    m_list_algo[i].setPosition(100, 35 * i + add_val_pos_x_drop_down);
    m_list_algo[i].setString(list_of_algo[i]);
  }

  for (int i = 0; i < end_iter; i++)
    m_list_algorithms[i].setPosition(50,
                                     50 * i + add_val_pos_x_categories_before);
  for (int i = end_iter; i < NUMBER_OF_ALGORITHMS; i++) {
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

void Visualizer::initialize_algorithms() {
  //------------------------------------------- SORTING
  algorithm_map[{Algocat::SORTING, 0}] = [this]() {
    *current_screen = sort_class;
    sort_class->insertion_sort();
  };
  algorithm_map[{Algocat::SORTING, 1}] = []() {
    std::cout << "Selection Sort\n";
  };
  algorithm_map[{Algocat::SORTING, 2}] = []() {
    std::cout << "Merge Sort\n";
  };
  algorithm_map[{Algocat::SORTING, 3}] = []() {
    std::cout << "Bubble Sort\n";
  };
  algorithm_map[{Algocat::SORTING, 4}] = []() {
    std::cout << "Heap Sort\n";
  };
  algorithm_map[{Algocat::SORTING, 5}] = []() {
    std::cout << "Quick Sort\n";
  };
  algorithm_map[{Algocat::SEARCHING, 0}] = []() {
    //------------------------------------------- SEARCHING
    std::cout << "Linear Search\n";
  };
  algorithm_map[{Algocat::SEARCHING, 1}] = []() {
    std::cout << "Binary Search\n";
  };
  //------------------------------------------- DATA STRUCTURES
  algorithm_map[{Algocat::DS, 0}] = []() {
    std::cout << "Stack\n";
  };
  algorithm_map[{Algocat::DS, 1}] = []() {
    std::cout << "Queue\n";
  };
  algorithm_map[{Algocat::DS, 2}] = []() {
    std::cout << "Linked List\n";
  };
  algorithm_map[{Algocat::DS, 3}] = []() {
    std::cout << "Hash Table\n";
  };
  algorithm_map[{Algocat::DS, 4}] = []() {
    std::cout << "Binary Search Tree\n";
  };
  algorithm_map[{Algocat::DS, 5}] = []() {
    std::cout << "Red-Black Tree\n";
  };
  algorithm_map[{Algocat::DS, 6}] = []() {
    std::cout << "AVL Tree\n";
  };
  algorithm_map[{Algocat::DS, 7}] = []() {
    std::cout << "Treaps\n";
  };
  //------------------------------------------- DYNAMIC PROGRAMMING
  algorithm_map[{Algocat::DYNAMIC, 0}] = []() {
    std::cout << "Cut Rod\n";
  };
  algorithm_map[{Algocat::DYNAMIC, 1}] = []() {
    std::cout << "Cut Rod (Memo)\n";
  };
  algorithm_map[{Algocat::DYNAMIC, 2}] = []() {
    std::cout << "Cut Rod (Tab)\n";
  };
  algorithm_map[{Algocat::DYNAMIC, 3}] = []() {
    std::cout << "Longest Common Subsequence\n";
  };
  //------------------------------------------- GREEDY
  algorithm_map[{Algocat::GREEDY, 0}] = []() {
    std::cout << "Huffman Codign\n";
  };
  algorithm_map[{Algocat::GREEDY, 1}] = []() {
    std::cout << "Activity Selector\n";
  };
  //------------------------------------------- ADVANCED DATA STRUCTURES
  algorithm_map[{Algocat::ADVANCEDDS, 0}] = []() {
    std::cout << "B-Tree\n";
  };
  algorithm_map[{Algocat::ADVANCEDDS, 1}] = []() {
    std::cout << "Fibonacci Tree\n";
  };
  algorithm_map[{Algocat::ADVANCEDDS, 2}] = []() {
    std::cout << "Van Emde Boas Tree\n";
  };
  //------------------------------------------- GRAPH
  algorithm_map[{Algocat::GRAPH, 0}] = []() {
    std::cout << "1\n";
  };
  algorithm_map[{Algocat::GRAPH, 1}] = []() {
    std::cout << "2\n";
  };
  algorithm_map[{Algocat::GRAPH, 2}] = []() {
    std::cout << "3\n";
  };
}

void Visualizer::go_to_algo_screen(int selected) {
  auto it = algorithm_map.find(std::make_pair(m_ac, selected));
  if (it != algorithm_map.end()) {
    it->second();  // ALGORITHM STYLES
    render();      // VISUALIZATION
  } else {
    std::cerr << "Algorithm not found" << std::endl;
  }
}

void Visualizer::render() {}

void Visualizer::typed_on(sf::Event input) {}
//------------------------------------------------------- Sorting

Sorting_Class::Sorting_Class(Screen** screen_ptr, Visualizer* viz_ptr)
    : current_screen(screen_ptr),
      visualize(viz_ptr),
      m_selected_sort_algo(0),
      m_selected_sorting_algo_index(0),
      m_char_size_text_variants(20),
      m_possible_input(false),
      m_temp_value("") {

  std::filesystem::current_path(
      std::filesystem::path(__FILE__).parent_path().parent_path());

  if (!m_open_sans.loadFromFile("assets/fonts/OpenSans-Regular.ttf")) {
    std::cerr << "Failed to load font" << std::endl;
  }

  //INITIALIZE VISUALIZATION BUTTONS
  int number_of_buttons = 4;
  m_visualization_buttons_names.resize(number_of_buttons);
  m_visualization_buttons_names = {"Start", "Example", "Worst case",
                                   "Best Case"};
  m_visualization_buttons_text.resize(number_of_buttons);
  m_visualization_buttons_shape.resize(number_of_buttons);
  visualization_buttons_style(150);
  // INITALIZE VISUALIZATION OPTIONS VECTOR WITH VALUES:
  // NUMBER OF ELEMENTS = 10, MINIMUM RANGE OF ELEMENTS = 0, MAXIMUM RANGE OF ELEMENTS = 100
  int number_of_options = 3;
  m_visualization_options_names.resize(number_of_options);
  m_visualization_options_names = {
      "Number of elemenst:", "Minimum value:", "Maximum value:"};
  m_visualization_options.resize(number_of_options);
  m_visualization_options = {10, 0, 100};
  m_textbox_input_style.resize(number_of_options);
  textbox(20, 3, 150);
}

Sorting_Class::~Sorting_Class() {}

void Sorting_Class::draw(sf::RenderWindow& window) {
  for (int i = 0; i < m_visualization_buttons_text.size(); i++) {
    window.draw(m_visualization_buttons_shape[i]);
    //window.draw(m_visualization_buttons_text[i]);
  }
  for (int i = 0; i < m_algorithm_variants.size(); i++)
    window.draw(m_algorithm_variants[i]);
  for (int i = 0; i < m_headers.size(); i++)
    window.draw(m_headers[i]);
  for (int i = 0; i < m_textbox_input_style.size(); i++)
    window.draw(m_textbox_input_style[i]);
}

void Sorting_Class::move_up() {
  if (!m_possible_input) {
    if (m_selected_sorting_algo_index - 1 >= 0) {
      if (m_selected_sorting_algo_index ==
          m_algorithm_variants.size() - m_visualization_options.size() -
              m_visualization_options_names.size() - 2)
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::Red);
      else
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::White);
      m_selected_sorting_algo_index--;
      m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
          sf::Color::Green);
      m_selected_sort_algo = m_selected_sorting_algo_index;
    }
  }
}

void Sorting_Class::move_down() {
  if (!m_possible_input) {
    if (m_selected_sorting_algo_index + 1 < m_algorithm_variants.size()) {
      if (m_selected_sorting_algo_index ==
          m_algorithm_variants.size() - m_visualization_options.size() -
              m_visualization_options_names.size() - 2)
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::Red);
      else
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::White);
      m_selected_sorting_algo_index++;
      m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
          sf::Color::Green);
      m_selected_sort_algo = m_selected_sorting_algo_index;
    }
  }
}

void Sorting_Class::move_left() {
  if (!m_possible_input) {
    if (!(m_selected_sorting_algo_index <
          m_algorithm_variants.size() - m_visualization_options.size() -
              m_visualization_buttons_names.size())) {
      if (m_selected_sorting_algo_index ==
          m_algorithm_variants.size() - m_visualization_options.size() - 1 -
              m_visualization_buttons_names.size())
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::Red);
      else
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::White);
      if (m_selected_sorting_algo_index >
              m_algorithm_variants.size() -
                  m_visualization_options_names.size() -
                  m_visualization_buttons_names.size() - 1 &&
          m_selected_sorting_algo_index <=
              m_algorithm_variants.size() -
                  m_visualization_buttons_names.size() - 1) {
        m_selected_sorting_algo_index = 0;
        m_selected_sort_algo = m_selected_sorting_algo_index;
        m_algorithm_variants[m_selected_sort_algo].setFillColor(
            sf::Color::Green);
      } else {
        m_selected_sorting_algo_index = m_algorithm_variants.size() -
                                        m_visualization_options.size() -
                                        m_visualization_buttons_names.size();
        m_selected_sort_algo = m_selected_sorting_algo_index;
        m_algorithm_variants[m_selected_sort_algo].setFillColor(
            sf::Color::Green);
      }
    }
  }
}

void Sorting_Class::move_right() {
  if (!m_possible_input) {
    if (!(m_selected_sorting_algo_index >=
          m_algorithm_variants.size() - m_visualization_buttons_names.size())) {
      if (m_selected_sorting_algo_index ==
          m_algorithm_variants.size() - m_visualization_options.size() -
              m_visualization_buttons_names.size() - 1)
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::Red);
      else
        m_algorithm_variants[m_selected_sorting_algo_index].setFillColor(
            sf::Color::White);
      if (m_selected_sorting_algo_index <
              m_algorithm_variants.size() -
                  m_visualization_buttons_names.size() &&
          !(m_selected_sorting_algo_index >=
            m_algorithm_variants.size() - m_visualization_buttons_names.size() -
                m_visualization_options.size())) {
        m_selected_sorting_algo_index = m_algorithm_variants.size() -
                                        m_visualization_options.size() -
                                        m_visualization_buttons_names.size();
        m_selected_sort_algo = m_selected_sorting_algo_index;
        m_algorithm_variants[m_selected_sort_algo].setFillColor(
            sf::Color::Green);
      } else if (m_selected_sorting_algo_index <
                 m_algorithm_variants.size() -
                     m_visualization_buttons_names.size()) {
        m_selected_sorting_algo_index =
            m_algorithm_variants.size() - m_visualization_buttons_names.size();
        m_selected_sort_algo = m_selected_sorting_algo_index;
        m_algorithm_variants[m_selected_sort_algo].setFillColor(
            sf::Color::Green);
      }
    }
  }
}

int Sorting_Class::pressed() {
  return m_selected_sort_algo;
}

void Sorting_Class::change_option(int selected) {
  switch (selected) {
    case 0:
      std::cout << "INSERTION SORT\n";
      break;
    case 1:
      std::cout << "Recursive Insertion Sort\n";
      break;
    case 2:
      std::cout << "Shell Sort\n";
      break;
    case 3:
      std::cout << "Binary Insertion Sort\n";
      break;
    case 4:
      std::cout << "Library Sort\n";
      break;
    case 5:
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
  }
}

void Sorting_Class::drop_down(int option) {}

void Sorting_Class::set_style(std::vector<std::string> variants, int pos_y) {
  m_algorithm_variants.resize(variants.size());
  for (int i = 0; i < variants.size(); i++) {
    m_algorithm_variants[i].setFont(m_open_sans);
    m_algorithm_variants[i].setFillColor(sf::Color::White);
    m_algorithm_variants[i].setCharacterSize(m_char_size_text_variants);
    m_algorithm_variants[i].setStyle(sf::Text::Bold);
    m_algorithm_variants[i].setPosition(50, 50 * i + pos_y);
    m_algorithm_variants[i].setString(variants[i]);
  }
  m_algorithm_variants[variants.size() - 1 - m_visualization_options.size() -
                       m_visualization_buttons_names.size()]
      .setFillColor(sf::Color::Red);
  m_algorithm_variants[0].setFillColor(sf::Color::Green);
  int count = 0;
  for (int i = variants.size() - m_visualization_options.size() -
               m_visualization_buttons_names.size();
       i < variants.size() - m_visualization_buttons_names.size(); i++) {
    m_algorithm_variants[i].setPosition(460, 50 * count + pos_y);
    count++;
  }
  count = 0;
  int temp = 0;
  for (int i = variants.size() - m_visualization_options_names.size() - 1;
       i < m_algorithm_variants.size(); i++) {
    m_algorithm_variants[i].setCharacterSize(35);
    sf::FloatRect text_bounds = m_algorithm_variants[i].getLocalBounds();
    m_algorithm_variants[i].setPosition(890 + (100 - text_bounds.width / 2),
                                        temp + 60 * count + pos_y);
    count++;
    temp = 100;
  }
  int number_of_headers = 3;
  m_headers_text = {"Variants", "Options", "Visulization"};
  m_headers_text.resize(number_of_headers);
  m_headers.resize(number_of_headers);
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
  insertion_sort_variants.insert(insertion_sort_variants.end(),
                                 m_visualization_options_names.begin(),
                                 m_visualization_options_names.end());
  insertion_sort_variants.insert(insertion_sort_variants.end(),
                                 m_visualization_buttons_names.begin(),
                                 m_visualization_buttons_names.end());
  set_style(insertion_sort_variants, 150);
}

void Sorting_Class::textbox(int char_size_textbox, int number_of_inputs,
                            int pos_y) {
  for (int i = 0; i < number_of_inputs; i++) {
    m_textbox_input_style[i].setFont(m_open_sans);
    m_textbox_input_style[i].setFillColor(sf::Color::White);
    m_textbox_input_style[i].setCharacterSize(m_char_size_text_variants);
    m_textbox_input_style[i].setPosition(690, 50 * i + pos_y);
    m_textbox_input_style[i].setString(
        std::to_string(m_visualization_options[i]));
  }
}

void Sorting_Class::typed_on(sf::Event input) {
  if (m_possible_input) {
    int char_typed = input.text.unicode;
    if ((char_typed >= 48 && char_typed <= 57) || char_typed == DELETE_KEY ||
        char_typed == ENTER_KEY || char_typed == MINUS_KEY) {
      if (m_selected_input_option == 0 && char_typed == MINUS_KEY)
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
    /*m_visualization_buttons_text[i].setFont(m_open_sans);
    m_visualization_buttons_text[i].setFillColor(sf::Color::White);
    m_visualization_buttons_text[i].setCharacterSize(35);
    m_visualization_buttons_text[i].setString(m_visualization_buttons_names[i]);*/
    //sf::FloatRect text_bounds = m_algorithm_variants[i].getLocalBounds();
    m_visualization_buttons_text[i].setPosition(
        890 + (100 - (m_visualization_buttons_names[i].length() * 35) / 2),
        temp + 60 * i + pos_y);
    temp = 100;
  }
}
