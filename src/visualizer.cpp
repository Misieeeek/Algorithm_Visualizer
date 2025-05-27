#include "visualizer.h"
#include <memory>
#include "visualization.h"

Visualizer::Visualizer(std::shared_ptr<Screen>& screen_ptr,
                       std::shared_ptr<Screen> menu, sf::RenderWindow* window)
    : current_screen(screen_ptr),
      main_menu(menu),
      window_ptr(window),
      m_selected_algorithm_index(0),
      m_selected_algorithm(0),
      m_category_option(true),
      m_category_font_size(35),
      m_drop_down_item_font_size(20) {
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
  m_algo_sort = {"Insertion Sorts", "Selection Sorts",    "Merge Sorts",
                 "Exchange Sorts",  "Distribution Sorts", "Concurrent Sorts"};
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

void Visualizer::init_visualizer_categories() {
  viz_opt = std::make_shared<Visualization_Options>(
      current_screen, shared_from_this(), window_ptr);
  viz_opt->init_visualization();
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
      current_screen = main_menu;
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
    current_screen = viz_opt;
    viz_opt->insertion_sort();
    viz_opt->initalize_sorting_algos();
    std::vector<std::string> names{"Normal", "Recursive", "Binary"};
    viz_opt->set_selected_algo_variants(
        0, [this]() { viz_opt->insertion_sort(); }, names, 4,
        "Variations: ", true);
  };
  algorithm_map[{algo_cat::sorting, 1}] = [this]() {
    current_screen = viz_opt;
    viz_opt->selection_sort();
    viz_opt->initalize_sorting_algos();
  };
  algorithm_map[{algo_cat::sorting, 2}] = [this]() {
    current_screen = viz_opt;
    viz_opt->merge_sort();
    viz_opt->initalize_sorting_algos();
  };
  algorithm_map[{algo_cat::sorting, 3}] = [this]() {
    current_screen = viz_opt;
    viz_opt->exchange_sort();
    viz_opt->initalize_sorting_algos();
  };
  algorithm_map[{algo_cat::sorting, 4}] = [this]() {
    current_screen = viz_opt;
    viz_opt->distribution_sort();
    viz_opt->initalize_sorting_algos();
  };
  algorithm_map[{algo_cat::sorting, 5}] = [this]() {
    current_screen = viz_opt;
    viz_opt->concurrent_sort();
    viz_opt->initalize_sorting_algos();
  };
}
void Visualizer::initialize_searching() {
  algorithm_map[{algo_cat::searching, 0}] = [this]() {
    current_screen = viz_opt;
    viz_opt->linear_search();
    viz_opt->initalize_searching_algos();
    std::vector<std::string> names{};
    viz_opt->set_selected_algo_variants(
        0, [this]() { viz_opt->linear_search(); }, names, 4,
        "Search value:", false);
  };
  algorithm_map[{algo_cat::searching, 1}] = [this]() {
    current_screen = viz_opt;
    viz_opt->binary_search();
    viz_opt->initalize_searching_algos();
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
