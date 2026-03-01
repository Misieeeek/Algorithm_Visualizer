#ifndef VISUALIZATION_OPTIONS_H
#define VISUALIZATION_OPTIONS_H
#pragma once

#include <memory>
#include <unordered_map>
#include "visualizer.h"

class Visualization_Options
    : public Screen,
      public std::enable_shared_from_this<Visualization_Options> {
 public:
  // IHERITENCE FROM CLASS SCREEN
  void draw(sf::RenderWindow& window) override;
  void move_up() override;
  void move_down() override;
  void move_left() override;
  void move_right() override;
  int pressed() override;
  void change_option(int selected) override;
  void typed_on(sf::Event input) override;

  Visualization_Options();
  Visualization_Options(std::shared_ptr<Screen>& screen_ptr,
                        std::shared_ptr<Visualizer> viz_ptr,
                        sf::RenderWindow* window);  // MENU HAS TO CHANGE
                                                    // TO VISUALIZER
  virtual ~Visualization_Options() = default;

  // MAKE shared_ptr FROM this
  void init_visualization_default();
  void init_visualization();

  //SET STYLE FOR SORT ALGO
  void set_style(std::vector<std::string> variants, int y_pos);
  void insertion_sort();
  void selection_sort();
  void merge_sort();
  void exchange_sort();
  void distribution_sort();
  void concurrent_sort();

  //SET STYLE FOR SEARCH ALGO
  void linear_search();
  void binary_search();

  void textbox(int char_size_textbox, std::size_t number_of_inputs, int pos_y);

  // RESPONSIBLE FOR CHANDELING INPUTBOX
  void input_box_selected(int item);

  // SET STYLE FOR VISUALIZATION BUTTONS
  void visualization_buttons_style(int pos_x);

  // VISUALIZE ALGORITHM WITH GIVEN ELEMENTS, MIN VALUE AND MAX VALUE
  void algo_viz(std::size_t n_elements, int min_val, int max_val);
  // OVERLOAD algo_viz(...) FUNCTION, ADDITIONAL PARAMETER case, WHERE false = WORST CASE
  void algo_viz(std::size_t n_elements, int min_val, int max_val, bool bw_case);

  // SET INSERTION SORT PARAMS
  void set_selected_algo_variants(int selected,
                                  std::function<void()> category_func,
                                  std::vector<std::string>& names,
                                  size_t opt_size, std::string name_of_input,
                                  bool additional);

  // STATE OF SELECTED SORTING ALGORITHM CATEGORY
  enum class algo_subcat {
    insertion_sort,
    selection_sort,
    merge_sort,
    exchange_sort,
    distribution_sort,
    concurrent_sort,
    linear_search,
    binary_search
  };

  // COMPARATOR FOR STD::PAIR<ALGO_SUBCAT, INT> TO BE USED IN THE MAP
  struct algo_subcat_pair_comparator {
    bool operator()(const std::pair<algo_subcat, int>& lhs,
                    const std::pair<algo_subcat, int>& rhs) const {
      if (lhs.first != rhs.first)
        return lhs.first < rhs.first;  // COMPARE CATEGORIES FIRST
      return lhs.second < rhs.second;  // THEN COMPARE THE INDEX
    }
  };

  // CUSTOM HASH FUNCTION FOR STD::PAIR<STD::STRING, INT>
  struct pair_hash {
    std::size_t operator()(const std::pair<std::string, int>& pair) const {
      auto hash1 = std::hash<std::string>{}(pair.first);
      auto hash2 = std::hash<int>{}(pair.second);
      return hash1 ^ (hash2 << 1);  // COMBINE THE TWO HASHES
    }
  };

  //FIND ALGO IN M_SORT_MAP
  void find_algo(int selected);

  //FIND OPTION IN M_VIZ_OPT_MAP
  void find_option(int selected);

  // SETS SETTINGS FOR SELECTED ALGO, PREPARATION FOR VISUALIZATIO
  void set_setting_selected_algo(int selected, std::function<void()> func);

  // INITALIZE CATEGORY ALGORITHM OPTION SELECTOR
  void initalize_sorting_algos();
  void initalize_searching_algos();

  // CHANGE OPTION PLACEMENT IN THE ARRAY
  void additional_option(bool additional);

  // SET DEFAULT OPTIONS SETTINGS
  void set_default_options();

  // SET LEFT/RIGHT BUTTONS
  void display_lr_buttons(bool display);

  // GET SELECTED ADDITIONAL OPTION INDEX
  int get_additional_option_index();
  // SET ADDITIONAL OPTION INDEX
  void set_additional_option_index(int value);

  // INITALIZE FUNCITONS TO GET DISPLAY NAME
  std::string get_display_name();

  // INITALIZE FULL NAME OF ALGO TO MAP
  // INITALIZE SORTING
  void init_sort_category_display_name();
  // INITALIZE SUBSECTION OF SORTING ALGORITHMS
  void init_insertion_sort_display_name();
  void init_selection_sort_display_name();
  void init_merge_sort_display_name();

  // INITALIZE FULL NAME OF ALGO TO MAP
  // INITALIZE SEARCHING
  void init_search_category_display_name();

  // HASH MAP FOR FULL ALGORITHMS NAMES WITH ITS VARIANTS
  std::unordered_map<std::pair<std::string, int>, std::string, pair_hash>
      m_display_name;

 private:
  // DISPLAYS SCREEN FOR SORTING
  std::shared_ptr<Screen> g_dummy_screen{nullptr};
  std::shared_ptr<Screen>& current_screen;
  std::shared_ptr<Visualizer> visualize;
  std::shared_ptr<Visualization> final_visual;
  sf::RenderWindow* window_ptr;

  // RESPONSIBLE FOR KEYBOARD MOVEMENT
  int m_selected_algo_index{0};

  // CHOOSED ALGO, HOLDS VALUE OF SELECTED ALGO
  int m_choosed_algo{0};

  //STATE OF SELECTED ALGO SUB-CATEGORY
  algo_subcat m_asc;
  //INITALIZE DIFFERENCT SORTING ALGOS LIST
  void initialize_insertion();
  void initialize_selection();
  void initialize_merge();
  void initialize_exchange();
  void initialize_distribution();
  void initialize_concurrent();

  //INITALIZE DIFFERENT SEARCHING ALGOS LIST
  void initialize_linear();
  void initialize_binary();

  // ALGO MAP(CATEGORY, INDEX)
  std::map<std::pair<algo_subcat, int>, std::function<void()>,
           algo_subcat_pair_comparator>
      m_algo_map;
  // SORTING CLASS MAP(M_SORT_MAP, OPTIONS, BUTTONS)
  std::unordered_map<int, std::function<void()>> m_sort_class_map;
  // CONSTANTS
  // LISTED IMPORTANT KEYS
  static constexpr int c_delete_key = 8;
  static constexpr int c_enter_key = 13;
  static constexpr int c_minus_key = 45;
  // HOLDING THE SIZE OF CERTAIN ELEMENTS
  static constexpr int c_headers = 3;
  static constexpr int c_input = 3;
  static constexpr int c_buttons = 4;

  // LIST OF ALGORITHMS VARIANTS, VARIES BY SORTING ALGORITHM
  // //STORES VARIANTS, OPTIONS, BUTTONS
  std::vector<sf::Text> m_algorithm_variants;
  std::size_t
      m_all_options_size;       // STORES SIZE OF VARIANTS + OPTIONS + BUTTONS
  std::size_t m_variants_size;  //STORES SIZE OF VARIANTS

  // TEXT STYLE & HEADERS
  int m_char_size_text_variants{20};
  std::array<std::string, c_headers> m_headers_text;
  std::array<sf::Text, c_headers> m_headers;

  // VISUALIZATION OPTIONS
  // THIS VECTOR KEEPS STATE OF:
  // NUMBER OF ELEMENTS, MINIMUM RANGE OF NUMBERS, MAXIMUM RANGE OF NUMBERS, OPTIONAL PARAMETER
  std::vector<int> m_visualization_options{10, 0, 100};
  std::vector<std::string> m_visualization_options_names{
      "Number of elements:", "Minimum value:", "Maximum value:"};
  std::size_t m_option_size{3};

  // VISUALIZATION BUTTONS
  std::array<std::string, c_buttons> m_visualization_buttons_names{
      "Start", "Example", "Worst case", "Best Case"};
  std::array<sf::Text, c_buttons> m_visualization_buttons_text;
  std::array<sf::RectangleShape, c_buttons> m_visualization_buttons_shape;

  // INPUT FOR OPTIONS
  std::array<sf::Text, c_input> m_textbox_input_style;
  std::ostringstream m_text_input;
  int m_selected_input_option;
  std::string m_temp_value{""};

  // IF THE IMPUT OPTION IS SELECTED
  bool m_possible_input{false};

  // KEEPS STATE IF ADDITIONAL PARAMETER IS OPEN
  bool m_additional_param{false};

  // KEEPS STATE IF ADDIOTIONAL PARAMETER EXISTS
  bool m_additional_exists{true};

  // LIST OF DIFFERENT SHELL SEQUENCE GAPS
  sf::Text m_additional_option{};
  std::vector<std::string> m_additional_option_names;

  // KEEPS THE STATE OF CURRENT ADDITIONAL OPTION INDEX
  int m_additional_option_index{0};

  // SHAPE OF LEFT/RIGHT BUTTONS
  std::vector<sf::RectangleShape> m_lr_btn_shape;
  std::vector<sf::ConvexShape> m_triangle_arrow;

  //
  size_t m_added_options;

  // INPUT LOGIC
  void input_logic(int char_typed);

  // DELETE INPUT
  void delete_last_char();

  //
  void set_input_params_by_sub_category();
  //
  void set_input_params_is();
  void set_input_params_ss();
  void set_input_params_ms();
  void set_input_params_es();
  void set_input_params_ds();
  void set_input_params_cs();
  void set_input_params_ls();
  void set_input_params_bs();

  //
  void make_lr_button_disappear();
};

#endif
