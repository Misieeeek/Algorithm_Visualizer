#ifndef VISUALIZER_H
#define VISUALIZER_H
#pragma once

#include <memory>
#include "main_window.h"

// FORWARD DECLARATION OF CLASS Visualization_Options and Visualization
class Visualization_Options;
class Search_Class;
class Visualization;

class Visualizer : public Screen,
                   public std::enable_shared_from_this<Visualizer> {
 public:
  Visualizer(std::shared_ptr<Screen>& screen_ptr, std::shared_ptr<Screen> menu,
             sf::RenderWindow* window);
  virtual ~Visualizer() = default;

  // MAKE shared_ptr FROM this
  void init_visualizer_categories();
  // RESPOSIBLE FOR DRAWING EVERYTHING
  void draw(sf::RenderWindow& window) override;
  // MOVE UP/DOWN (OPTIONS)
  void move_up() override;
  void move_down() override;
  // RETURN A NUMBER OF WHICH OPTION WAS PRESSED
  int pressed() override;
  // RESPONSIBLE FOR CHANGING THE OPTION (WHEN SELECTED, DO SOMETHING)
  void change_option(int selected) override;
  // RESPOSIBLE FOR DROP DOWN MENUS OF EACH CATEGORY OF ALGORITHMS
  void drop_down(int option) override;
  // RESPONSIBLE FOR STYLE OF DROP DOWN MENU
  void general_algo_list(std::size_t number_of_categories,
                         std::span<std::string> list_of_algo, int end_iter,
                         int add_val_pos_x_drop_down,
                         int add_val_pos_x_categories_before,
                         int adda_val_pos_x_categories_afer);
  // RESPONSIBLE FOR FINDING THE SELECTED ALGORITHM AND ACTIVATING IT FROM DOWN
  // MENU
  void go_to_algo_screen(int selected);

  // RESPONSIBLE FOR LOADING ALGORITHM SCREENS
  void initialize_algorithms();

  // STATE OF PRESSED CATEGORY
  enum class algo_cat {
    sorting,
    searching,
    ds,
    dynamic,
    greedy,
    advancedds,
    graph,
    none
  };

  // COMPARATOR FOR STD::PAIR<ALGOCAT, INT> TO BE USED IN THE MAP
  struct algocat_pair_comparator {
    bool operator()(const std::pair<algo_cat, int>& lhs,
                    const std::pair<algo_cat, int>& rhs) const {
      if (lhs.first != rhs.first)
        return lhs.first < rhs.first;  // Compare categories first
      return lhs.second < rhs.second;  // Then compare the index
    }
  };

 private:
  // KEEPS THE STATE OF ALGOCAT CURRENTLY SELECTED
  algo_cat m_ac;

  // MAIN MENU FOR EVERY CATEGORY OF ALGORITHMS
  std::shared_ptr<Screen>& current_screen;
  std::shared_ptr<Screen> main_menu;
  std::shared_ptr<Visualization_Options> viz_opt;
  std::shared_ptr<Search_Class> search_class;
  sf::RenderWindow* window_ptr;
  int m_selected_algorithm_index{0};
  static constexpr std::size_t c_num_algos{8};
  std::array<sf::Text, c_num_algos> m_list_algorithms;
  int m_selected_algorithm{0};

  // DROP DOWN MENU ITEMS LIST
  std::vector<sf::Text> m_list_algo;

  // CONSTANTS FOR NUMBER OF ALGORITHMS IN DIFFERENT CATEGORIES
  static constexpr std::size_t c_num_sort = 6;
  static constexpr std::size_t c_num_search = 2;
  static constexpr std::size_t c_num_ds = 8;
  static constexpr std::size_t c_num_dynamic = 4;
  static constexpr std::size_t c_num_greedy = 2;
  static constexpr std::size_t c_num_advancedds = 3;
  static constexpr std::size_t c_num_graph = 3;

  // DROP DOWN MENU FOR SORTING ALGORITHMS
  std::array<sf::Text, c_num_sort> m_list_algo_sort;
  std::array<std::string, c_num_sort> m_algo_sort{
      "Insertion Sorts", "Selection Sorts",    "Merge Sorts",
      "Exchange Sorts",  "Distribution Sorts", "Concurrent Sorts"};

  // DROP DOWN MENU FOR SEARCH ALGORITHMS
  std::array<sf::Text, c_num_search> m_list_algo_search;
  std::array<std::string, c_num_search> m_algo_search{"Linear Search",
                                                      "Binary Search"};

  // DROP DOWN MENU FOR DS ALGORITHMS
  std::array<sf::Text, c_num_ds> m_list_algo_ds;
  std::array<std::string, c_num_ds> m_algo_ds{"Stack",
                                              "Queue",
                                              "Linked List",
                                              "Hash Table",
                                              "Binary Search Tree",
                                              "Red-Black Tree",
                                              "AVL Tree",
                                              "Treaps"};

  // DROP DOWN MENU FOR DYNAMIC PROGRAMMING ALGORITHMS
  std::array<sf::Text, c_num_dynamic> m_list_algo_dynamic;
  std::array<std::string, c_num_dynamic> m_algo_dynamic{
      "Cut Rod", "Cut Rod (Memoization)", "Cut Rod (Tabulation)",
      "Longest Common Subsequence"};

  // DROP DOWN MENU FOR GREEDY ALGORITHMS
  std::array<sf::Text, c_num_greedy> m_list_algo_greedy;
  std::array<std::string, c_num_greedy> m_algo_greedy{"Huffman Coding",
                                                      "Activity Selector"};

  // DROP DOWN MENU FOR ADVANCED DATA STRUCTURES ALGORITHMS
  std::array<sf::Text, c_num_advancedds> m_list_algo_advancedds;
  std::array<std::string, c_num_advancedds> m_algo_advancedds{
      "B-Tree", "Fibonacci Heap", "Van Emde Boas Tree"};

  // DROP DOWN MENU FOR GRAPH ALGORITHMS
  std::array<sf::Text, c_num_graph> m_list_algo_graph;
  std::array<std::string, c_num_graph> m_algo_graph{"1", "2", "3"};

  // TEXT STYLES
  const int m_category_font_size{35};
  const int m_drop_down_item_font_size{20};

  // DROP DOWN MENU COUNTERS AND CHECKER FOR CATEGORY OPTION
  int m_dropped_items;
  int m_dropped_items_index;
  bool m_category_option{true};

  // INITIALIZE ALGORITHM MAP, DIVIDED PER CATEGORY
  void initialize_sorting();
  void initialize_searching();
  void initialize_ds();
  void initialize_dynamic();
  void initialize_greedy();
  void initialize_advancedds();
  void initialize_graph();

  // ALGORITHM MAP(CATEGORY, INDEX)
  std::map<std::pair<algo_cat, int>, std::function<void()>,
           algocat_pair_comparator>
      algorithm_map;

  //void generate_visualization() {};
};

#endif
