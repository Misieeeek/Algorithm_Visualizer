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
    set_selected_algo_variants(
        0, [this]() { insertion_sort(); }, names, 4, "Variations: ", true);
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
    set_selected_algo_variants(
        1, [this]() { insertion_sort(); }, names, 4, "Gap: ", true);
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

void Visualization_Options::init_insertion_sort_display_name() {
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
}

void Visualization_Options::init_selection_sort_display_name() {
  m_display_name[std::make_pair(std::string("Selection Sort"), 0)] =
      "Selection Sort";
}

void Visualization_Options::init_merge_sort_display_name() {
  m_display_name[std::make_pair(std::string("Merge Sort"), 0)] = "Merge Sort";
}

void Visualization_Options::init_sort_category_display_name() {
  init_insertion_sort_display_name();
  init_selection_sort_display_name();
  init_merge_sort_display_name();
}
