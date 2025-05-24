#include <filesystem>
#include <memory>
#include "main_window.h"
#include "visualization.h"
#include "visualization_options.h"

void Visualization_Options::initalize_searching_algos() {
  initialize_linear();
  initialize_binary();
  init_search_category_display_name();
}

void Visualization_Options::initialize_linear() {
  m_algo_map[{algo_subcat::linear_search, 0}] = [this]() {  // LINEAR SEARCH
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    linear_search();
  };
  additional_option(false);
}

void Visualization_Options::initialize_binary() {
  m_algo_map[{algo_subcat::binary_search, 0}] = [this]() {  // BINARY SEARCH
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    binary_search();

  };
  additional_option(false);
}

void Visualization_Options::linear_search() {
  std::vector<std::string> linear_search_variants = {"Linear Search", "Back"};
  m_variants_size = linear_search_variants.size();
  linear_search_variants.insert(linear_search_variants.end(),
                                m_visualization_options_names.begin(),
                                m_visualization_options_names.end());
  linear_search_variants.insert(linear_search_variants.end(),
                                m_visualization_buttons_names.begin(),
                                m_visualization_buttons_names.end());
  set_style(linear_search_variants, 150);
  m_asc = algo_subcat::linear_search;
}

void Visualization_Options::binary_search() {
  std::vector<std::string> linear_search_variants = {"Binary Search", "Back"};
  m_variants_size = linear_search_variants.size();
  linear_search_variants.insert(linear_search_variants.end(),
                                m_visualization_options_names.begin(),
                                m_visualization_options_names.end());
  linear_search_variants.insert(linear_search_variants.end(),
                                m_visualization_buttons_names.begin(),
                                m_visualization_buttons_names.end());
  set_style(linear_search_variants, 150);
  m_asc = algo_subcat::binary_search;
}

void Visualization_Options::init_search_category_display_name() {
  m_display_name[std::make_pair(std::string("Linear Search"), 0)] =
      "Linear Search";
  m_display_name[std::make_pair(std::string("Binary Search"), 0)] =
      "Binary Search";
}
