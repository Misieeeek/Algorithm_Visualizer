#include <memory>
#include "visualization.h"
#include "visualization_options.h"

void Visualization_Options::initalize_sorting_algos() {
  initialize_insertion();
  initialize_selection();
  initialize_merge();
  initialize_exchange();
  initialize_distribution();
  initialize_concurrent();
  init_sort_category_display_name();
}

void Visualization_Options::initialize_insertion() {
  m_algo_map[{algo_subcat::insertion_sort, 0}] = [this]() {  // INSERTION SORT
    m_additional_exists = true;
    std::vector<std::string> names = {"Normal", "Recursive", "Binary"};
    set_selected_sort_variants(
        0, [this]() { insertion_sort(); }, names, "Variations: ");
  };
  m_algo_map[{algo_subcat::insertion_sort, 1}] = [this]() {  // SHELL SORT
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
  m_algo_map[{algo_subcat::insertion_sort, 2}] = [this]() {  // SPLAYSORT
    set_setting_selected_algo(2, [this]() { insertion_sort(); });
  };
  m_algo_map[{algo_subcat::insertion_sort, 3}] = [this]() {  // TREE SORT
    set_setting_selected_algo(3, [this]() { insertion_sort(); });
  };
  m_algo_map[{algo_subcat::insertion_sort, 4}] = [this]() {  // LIBRARY SORT
    set_setting_selected_algo(4, [this]() { insertion_sort(); });
  };
  m_algo_map[{algo_subcat::insertion_sort, 5}] = [this]() {  // PATIENCE SORT
    set_setting_selected_algo(5, [this]() { insertion_sort(); });
  };
  additional_option(false);
}
void Visualization_Options::initialize_selection() {
  m_algo_map[{algo_subcat::selection_sort, 0}] = [this]() {  // SELECTION SORT
    set_setting_selected_algo(0, [this]() { selection_sort(); });
  };
  m_algo_map[{algo_subcat::selection_sort, 1}] = [this]() {  // HEAPSORT
    set_setting_selected_algo(1, [this]() { selection_sort(); });
  };
  m_algo_map[{algo_subcat::selection_sort, 2}] = [this]() {  //SMOOTH SORT
    set_setting_selected_algo(2, [this]() { selection_sort(); });
  };
  m_algo_map[{algo_subcat::selection_sort, 3}] =
      [this]() {  // CARTESIAN TREE SORT
        set_setting_selected_algo(3, [this]() { selection_sort(); });
      };
  m_algo_map[{algo_subcat::selection_sort, 4}] = [this]() {  // TOURNAMENT SORT
    set_setting_selected_algo(4, [this]() { selection_sort(); });
  };
  m_algo_map[{algo_subcat::selection_sort, 5}] = [this]() {  // CYCLE SORT
    set_setting_selected_algo(5, [this]() { selection_sort(); });
  };
  m_algo_map[{algo_subcat::selection_sort, 6}] = [this]() {  // WEAK-HEAP SORT
    set_setting_selected_algo(6, [this]() { selection_sort(); });
  };
  additional_option(false);
}
void Visualization_Options::initialize_merge() {
  m_algo_map[{algo_subcat::merge_sort, 0}] = [this]() {
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    merge_sort();
  };
  m_algo_map[{algo_subcat::merge_sort, 1}] = [this]() {
    set_setting_selected_algo(1, [this]() { merge_sort(); });
  };
  m_algo_map[{algo_subcat::merge_sort, 2}] = [this]() {
    set_setting_selected_algo(2, [this]() { merge_sort(); });
  };
  m_algo_map[{algo_subcat::merge_sort, 3}] = [this]() {
    set_setting_selected_algo(3, [this]() { merge_sort(); });
  };
  m_algo_map[{algo_subcat::merge_sort, 4}] = [this]() {
    set_setting_selected_algo(4, [this]() { merge_sort(); });
  };
  additional_option(false);
}
void Visualization_Options::initialize_exchange() {
  m_algo_map[{algo_subcat::exchange_sort, 0}] = [this]() {
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    exchange_sort();
  };
  m_algo_map[{algo_subcat::exchange_sort, 1}] = [this]() {
    set_setting_selected_algo(1, [this]() { exchange_sort(); });
  };
  m_algo_map[{algo_subcat::exchange_sort, 2}] = [this]() {
    set_setting_selected_algo(2, [this]() { exchange_sort(); });
  };
  m_algo_map[{algo_subcat::exchange_sort, 3}] = [this]() {
    set_setting_selected_algo(3, [this]() { exchange_sort(); });
  };
  m_algo_map[{algo_subcat::exchange_sort, 4}] = [this]() {
    set_setting_selected_algo(4, [this]() { exchange_sort(); });
  };
  m_algo_map[{algo_subcat::exchange_sort, 5}] = [this]() {
    set_setting_selected_algo(5, [this]() { exchange_sort(); });
  };
  m_algo_map[{algo_subcat::exchange_sort, 6}] = [this]() {
    set_setting_selected_algo(6, [this]() { exchange_sort(); });
  };
  additional_option(false);
}
void Visualization_Options::initialize_distribution() {
  m_algo_map[{algo_subcat::distribution_sort, 0}] = [this]() {
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    distribution_sort();
  };
  m_algo_map[{algo_subcat::distribution_sort, 1}] = [this]() {
    set_setting_selected_algo(1, [this]() { distribution_sort(); });
  };
  m_algo_map[{algo_subcat::distribution_sort, 2}] = [this]() {
    set_setting_selected_algo(2, [this]() { distribution_sort(); });
  };
  m_algo_map[{algo_subcat::distribution_sort, 3}] = [this]() {
    set_setting_selected_algo(3, [this]() { distribution_sort(); });
  };
  m_algo_map[{algo_subcat::distribution_sort, 4}] = [this]() {
    set_setting_selected_algo(4, [this]() { distribution_sort(); });
  };
  m_algo_map[{algo_subcat::distribution_sort, 5}] = [this]() {
    set_setting_selected_algo(5, [this]() { distribution_sort(); });
  };
  m_algo_map[{algo_subcat::distribution_sort, 6}] = [this]() {
    set_setting_selected_algo(6, [this]() { distribution_sort(); });
  };
  m_algo_map[{algo_subcat::distribution_sort, 7}] = [this]() {
    set_setting_selected_algo(7, [this]() { distribution_sort(); });
  };
  m_algo_map[{algo_subcat::distribution_sort, 8}] = [this]() {
    set_setting_selected_algo(8, [this]() { distribution_sort(); });
  };
  m_algo_map[{algo_subcat::distribution_sort, 9}] = [this]() {
    set_setting_selected_algo(9, [this]() { distribution_sort(); });
  };
  additional_option(false);
}
void Visualization_Options::initialize_concurrent() {
  m_algo_map[{algo_subcat::concurrent_sort, 0}] = [this]() {
    m_choosed_algo = 0;
    set_default_options();
    additional_option(false);
    concurrent_sort();
  };
  m_algo_map[{algo_subcat::concurrent_sort, 1}] = [this]() {
    set_setting_selected_algo(1, [this]() { concurrent_sort(); });
  };
  m_algo_map[{algo_subcat::concurrent_sort, 2}] = [this]() {
    set_setting_selected_algo(2, [this]() { concurrent_sort(); });
  };
  m_algo_map[{algo_subcat::concurrent_sort, 3}] = [this]() {
    set_setting_selected_algo(3, [this]() { concurrent_sort(); });
  };
  additional_option(false);
}

void Visualization_Options::insertion_sort() {
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
  m_asc = algo_subcat::insertion_sort;
}

void Visualization_Options::selection_sort() {
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
  m_asc = algo_subcat::selection_sort;
}

void Visualization_Options::merge_sort() {
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
  m_asc = algo_subcat::merge_sort;
}

void Visualization_Options::exchange_sort() {
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
  m_asc = algo_subcat::exchange_sort;
}

void Visualization_Options::distribution_sort() {
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
  m_asc = algo_subcat::distribution_sort;
}

void Visualization_Options::concurrent_sort() {
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
  m_asc = algo_subcat::concurrent_sort;
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
