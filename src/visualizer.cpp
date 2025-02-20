#include "visualizer.h"
#include "main_menu.h"
#include "main_window.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>
#include <memory>
#include <utility>

std::map<std::pair<Algocat, int>, std::function<void()>,
         algocat_pair_comparator>
    algorithm_map;

Visualizer::Visualizer(Screen **screen_ptr, Screen *menu)
    : selected_algorithm_index(0), selected_algorithm(0),
      category_option(true) {

  std::filesystem::current_path(
      std::filesystem::path(__FILE__).parent_path().parent_path());

  if (!open_sans.loadFromFile("assets/fonts/OpenSans-Regular.ttf")) {
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
    list_algorithms[i].setFont(open_sans);
    list_algorithms[i].setFillColor(sf::Color::White);
    list_algorithms[i].setCharacterSize(category_font_size);
    list_algorithms[i].setStyle(sf::Text::Bold);
    list_algorithms[i].setPosition(50, 50 * i + 150);
    list_algorithms[i].setString(algo[i]);
  }
  list_algorithms[NUMBER_OF_ALGORITHMS - 1].setFillColor(sf::Color::Red);
  list_algorithms[0].setFillColor(sf::Color::Green);
  dropped = false;

  // INITIALIZE MAP FOR ALGORITHMS
  initialize_algorithms();
}

Visualizer::~Visualizer() { delete sort_class; }

void Visualizer::move_up() {
  if (dropped || !category_option) {
    if (dropped_items_index - 1 >= 0) {
      list_algo[dropped_items_index].setFillColor(sf::Color::White);
      dropped_items_index--;
      list_algo[dropped_items_index].setFillColor(sf::Color::Green);
      dropped_items = dropped_items_index;
    } else {
      category_option = true;
      list_algo[dropped_items_index].setFillColor(sf::Color::White);
      list_algorithms[selected_algorithm_index].setFillColor(sf::Color::Green);
    }
  } else {
    if (selected_algorithm_index - 1 >= 0) {
      if (selected_algorithm_index == NUMBER_OF_ALGORITHMS - 1)
        list_algorithms[selected_algorithm_index].setFillColor(sf::Color::Red);
      else
        list_algorithms[selected_algorithm_index].setFillColor(
            sf::Color::White);
      selected_algorithm_index--;
      list_algorithms[selected_algorithm_index].setFillColor(sf::Color::Green);
      selected_algorithm = selected_algorithm_index;
    }
  }
}

void Visualizer::move_down() {
  if (dropped) {
    if (dropped_items_index + 1 < list_algo.size()) {
      if (category_option) {
        category_option = false;
        list_algo[0].setFillColor(sf::Color::Green);
        list_algorithms[selected_algorithm_index].setFillColor(
            sf::Color::White);
      } else {
        list_algo[dropped_items_index].setFillColor(sf::Color::White);
        dropped_items_index++;
        list_algo[dropped_items_index].setFillColor(sf::Color::Green);
        dropped_items = dropped_items_index;
      }
    }
  } else {
    if (selected_algorithm_index + 1 < NUMBER_OF_ALGORITHMS) {
      list_algorithms[selected_algorithm_index].setFillColor(sf::Color::White);
      selected_algorithm_index++;
      list_algorithms[selected_algorithm_index].setFillColor(sf::Color::Green);
      selected_algorithm = selected_algorithm_index;
    }
  }
}

void Visualizer::move_left() {}
void Visualizer::move_right() {}

void Visualizer::draw(sf::RenderWindow &window) {
  opend = true;
  if (static_cast<int>(ac) >= 0 && static_cast<int>(ac) < 7) {
    for (int i = 0; i < list_algo.size(); i++)
      window.draw(list_algo[i]);
    for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++)
      window.draw(list_algorithms[i]);
  } else {
    for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++) {
      list_algorithms[i].setPosition(50, 50 * i + 150);
      window.draw(list_algorithms[i]);
    }
  }
}

void Visualizer::change_option(int selected) {
  if (!dropped) {        // Place where drop down menu is deactivated
    if (selected == 7) { // EXIT out of visualizer
      opend = false;
      selected_algorithm = 0;
      selected_algorithm_index = 0;
      list_algorithms[0].setFillColor(sf::Color::Green);
      list_algorithms[NUMBER_OF_ALGORITHMS - 1].setFillColor(sf::Color::Red);
      dropped = true;
      *current_screen = main_menu;
    } else {       // Every other option than EXIT
      if (opend) { // Prevents activating drop down menu comming from main menu
        dropped = true;
        dropped_items = 0;
        dropped_items_index = 0;
        drop_down(selected);
      } else {
        drop_down(7);
        dropped = false;
      }
    }
  } else {                 // Place where drop down menu is active
    if (category_option) { // currently standing at algorithm category
      dropped = false;
      drop_down(7);
    } else { // Place where drop down menus options are executed
      go_to_algo_screen(selected);
    }
  }
}

void Visualizer::drop_down(int option) {
  switch (option) {
  case 0:
    ac = Algocat::SORTING;
    general_algo_list(NUMBER_OF_SORT_ALGO, algo_sort, 1, 100, 50, 260);
    break;
  case 1:
    ac = Algocat::SEARCHING;
    general_algo_list(NUMBER_OF_SEARCH_ALGO, algo_search, 2, 250, 150, 220);
    break;
  case 2:
    ac = Algocat::DS;
    general_algo_list(NUMBER_OF_DS_ALGO, algo_ds, 3, 200, 50, 320);
    break;
  case 3:
    ac = Algocat::DYNAMIC;
    general_algo_list(NUMBER_OF_DYNAMIC_ALGO, algo_dynamic, 4, 300, 100, 230);
    break;
  case 4:
    ac = Algocat::GREEDY;
    general_algo_list(NUMBER_OF_GREEDY_ALGO, algo_greedy, 5, 390, 140, 210);
    break;
  case 5:
    ac = Algocat::ADVANCEDDS;
    general_algo_list(NUMBER_OF_ADVANCEDDS_ALGO, algo_advancedds, 6, 400, 100,
                      210);
    break;
  case 6:
    ac = Algocat::GRAPH;
    general_algo_list(NUMBER_OF_GRAPH_ALGO, algo_graph, 7, 445, 100, 185);
    break;
  case 7:
    ac = Algocat::NONE;
    break;
  }
}

void Visualizer::general_algo_list(int number_of_categories,
                                   std::vector<std::string> list_of_algo,
                                   int end_iter, int add_val_pos_x_drop_down,
                                   int add_val_pos_x_categories_before,
                                   int add_val_pos_x_categories_after) {
  list_algo.resize(number_of_categories);
  for (int i = 0; i < number_of_categories; i++) {
    list_algo[i].setFont(open_sans);
    list_algo[i].setFillColor(sf::Color::White);
    list_algo[i].setCharacterSize(drop_down_item_font_size);
    list_algo[i].setStyle(sf::Text::Bold);
    list_algo[i].setPosition(100, 35 * i + add_val_pos_x_drop_down);
    list_algo[i].setString(list_of_algo[i]);
  }

  for (int i = 0; i < end_iter; i++)
    list_algorithms[i].setPosition(50,
                                   50 * i + add_val_pos_x_categories_before);
  for (int i = end_iter; i < NUMBER_OF_ALGORITHMS; i++) {
    list_algorithms[i].setPosition(50, 50 * i + add_val_pos_x_categories_after);
  }
}

int Visualizer::pressed() {
  if (category_option)
    return selected_algorithm;
  else
    return dropped_items;
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
  algorithm_map[{Algocat::SORTING, 2}] = []() { std::cout << "Merge Sort\n"; };
  algorithm_map[{Algocat::SORTING, 3}] = []() { std::cout << "Bubble Sort\n"; };
  algorithm_map[{Algocat::SORTING, 4}] = []() { std::cout << "Heap Sort\n"; };
  algorithm_map[{Algocat::SORTING, 5}] = []() { std::cout << "Quick Sort\n"; };
  algorithm_map[{Algocat::SEARCHING, 0}] = []() {
    //------------------------------------------- SEARCHING
    std::cout << "Linear Search\n";
  };
  algorithm_map[{Algocat::SEARCHING, 1}] = []() {
    std::cout << "Binary Search\n";
  };
  //------------------------------------------- DATA STRUCTURES
  algorithm_map[{Algocat::DS, 0}] = []() { std::cout << "Stack\n"; };
  algorithm_map[{Algocat::DS, 1}] = []() { std::cout << "Queue\n"; };
  algorithm_map[{Algocat::DS, 2}] = []() { std::cout << "Linked List\n"; };
  algorithm_map[{Algocat::DS, 3}] = []() { std::cout << "Hash Table\n"; };
  algorithm_map[{Algocat::DS, 4}] = []() {
    std::cout << "Binary Search Tree\n";
  };
  algorithm_map[{Algocat::DS, 5}] = []() { std::cout << "Red-Black Tree\n"; };
  algorithm_map[{Algocat::DS, 6}] = []() { std::cout << "AVL Tree\n"; };
  algorithm_map[{Algocat::DS, 7}] = []() { std::cout << "Treaps\n"; };
  //------------------------------------------- DYNAMIC PROGRAMMING
  algorithm_map[{Algocat::DYNAMIC, 0}] = []() { std::cout << "Cut Rod\n"; };
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
  algorithm_map[{Algocat::ADVANCEDDS, 0}] = []() { std::cout << "B-Tree\n"; };
  algorithm_map[{Algocat::ADVANCEDDS, 1}] = []() {
    std::cout << "Fibonacci Tree\n";
  };
  algorithm_map[{Algocat::ADVANCEDDS, 2}] = []() {
    std::cout << "Van Emde Boas Tree\n";
  };
  //------------------------------------------- GRAPH
  algorithm_map[{Algocat::GRAPH, 0}] = []() { std::cout << "1\n"; };
  algorithm_map[{Algocat::GRAPH, 1}] = []() { std::cout << "2\n"; };
  algorithm_map[{Algocat::GRAPH, 2}] = []() { std::cout << "3\n"; };
}

void Visualizer::go_to_algo_screen(int selected) {
  auto it = algorithm_map.find(std::make_pair(ac, selected));
  if (it != algorithm_map.end()) {
    it->second(); // ALGORITHM STYLES
    render();     // VISUALIZATION
  } else {
    std::cerr << "Algorithm not found" << std::endl;
  }
}

void Visualizer::render() {}

//------------------------------------------------------- Sorting

Sorting_Class::Sorting_Class(Screen **screen_ptr, Visualizer *viz_ptr)
    : current_screen(screen_ptr), visualize(viz_ptr), selected_sort_algo(0),
      selected_sorting_algo_index(0) {

  std::cout << "Sorting_Class screen initialized with Visualizer access.\n";
  std::filesystem::current_path(
      std::filesystem::path(__FILE__).parent_path().parent_path());

  if (!open_sans.loadFromFile("assets/fonts/OpenSans-Regular.ttf")) {
    std::cerr << "Failed to load font" << std::endl;
  }
}

Sorting_Class::~Sorting_Class() {
  std::cout << "DESTRUCTOR SORTING" << std::endl;
}
void Sorting_Class::draw(sf::RenderWindow &window) {
  for (int i = 0; i < algorithm_variants.size(); i++)
    window.draw(algorithm_variants[i]);
}

void Sorting_Class::move_up() {
  std::cout << selected_sorting_algo_index << std::endl;
  if (selected_sorting_algo_index - 1 >= 0) {
    if (selected_sorting_algo_index == algorithm_variants.size() - 1)
      algorithm_variants[selected_sorting_algo_index].setFillColor(
          sf::Color::Red);
    else
      algorithm_variants[selected_sorting_algo_index].setFillColor(
          sf::Color::White);
    selected_sorting_algo_index--;
    algorithm_variants[selected_sorting_algo_index].setFillColor(
        sf::Color::Green);
    selected_sort_algo = selected_sorting_algo_index;
  }
}

void Sorting_Class::move_down() {
  if (selected_sorting_algo_index + 1 <
      algorithm_variants.size() - NUMBER_OF_SORT_OPTIONS) {
    algorithm_variants[selected_sorting_algo_index].setFillColor(
        sf::Color::White);
    selected_sorting_algo_index++;
    algorithm_variants[selected_sorting_algo_index].setFillColor(
        sf::Color::Green);
    selected_sort_algo = selected_sorting_algo_index;
  }
}

void Sorting_Class::move_left() {}

void Sorting_Class::move_right() {}

int Sorting_Class::pressed() { return selected_sort_algo; }

void Sorting_Class::change_option(int selected) {
  if (selected == algorithm_variants.size() - 1 - NUMBER_OF_SORT_OPTIONS) {
    selected_sort_algo = 0;
    selected_sorting_algo_index = 0;
    algorithm_variants[0].setFillColor(sf::Color::Green);
    algorithm_variants[algorithm_variants.size() - 1 - NUMBER_OF_SORT_OPTIONS]
        .setFillColor(sf::Color::Red);
    *current_screen = visualize;
  } else {
    std::cout << selected << std::endl;
  }
}

void Sorting_Class::drop_down(int option) {}

void Sorting_Class::set_style(std::vector<std::string> variants, int pos_y) {
  for (int i = 0; i < NUMBER_OF_SORT_OPTIONS; i++)

    algorithm_variants.resize(variants.size());
  for (int i = 0; i < variants.size(); i++) {
    algorithm_variants[i].setFont(open_sans);
    algorithm_variants[i].setFillColor(sf::Color::White);
    algorithm_variants[i].setCharacterSize(char_size);
    algorithm_variants[i].setStyle(sf::Text::Bold);
    algorithm_variants[i].setPosition(50, 50 * i + pos_y);
    algorithm_variants[i].setString(variants[i]);
  }
  algorithm_variants[variants.size() - 1 - NUMBER_OF_SORT_OPTIONS].setFillColor(
      sf::Color::Red);
  algorithm_variants[0].setFillColor(sf::Color::Green);
  for (int i = variants.size() - NUMBER_OF_SORT_OPTIONS; i < variants.size();
       i++)
    algorithm_variants[i].setPosition(550, 50 * i + pos_y);
}

void Sorting_Class::insertion_sort() {
  std::vector<std::string> insertion_sort_variants = {
      "Insertion Sort",     "Recursive Insertion Sort",
      "Shell Sort",         "Binary Insertion Sort",
      "Library Sort",       "Back",
      "Number of elements", "Minimum value",
      "Maximum value"};
  set_style(insertion_sort_variants, 150);
}
