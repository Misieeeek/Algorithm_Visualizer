#ifndef VISUALIZATION_H
#define VISUALIZATION_H
#pragma once

#include "sorting_class.h"

class Visualization : public Screen {
 public:
  Visualization(Screen** screen_ptr, Sorting_Class* sort_class_ptr,
                sf::RenderWindow* window);
  ~Visualization();

  void draw(sf::RenderWindow& window) override;
  void move_left() override;
  void move_right() override;
  int pressed() override;
  void change_option(int selected) override;

  void visual();

  // SET STYLES FOR SCREEN
  void set_styles();

  // SET PREVIOUSLY CHOOSED OPTIONS
  void set_options(std::size_t n_elements, int min_val, int max_val,
                   std::string algo_name);

  // RANDOM NUMBER GENERATOR
  int random_number_gen(int min_val, int max_val);

  //
  void standardize(std::vector<double>& box_pos, int number, int i);

  void update_rectangle_pos(int i, int number);

  void update_rectangle_color(int i, sf::Color c);

  void initialize_algorithms();
  void execute_algorithm(const std::string& name);

  void check_mutex_type();

  //SHELL SORT GAPS GENERATORS
  void set_shell_gaps();         //GO TO SELECTED GAP GENERATOR FUNCTION
  void shell_gap_shell();        // ORIGINAL SHELL GAP
  void shell_gap_fl();           // FRANK & LAZARUS GAP
  void shell_gap_hibbard();      // HIBBARD GAP
  void shell_gap_ps();           // PAPERNOV & STASEVICH GAP
  void shell_gap_pratt();        // PRATT GAP
  void shell_gap_knuth();        // KNUTH GAP
  void shell_gap_is();           // INCERPI & SEDGEWICK GAP
  void shell_gap_sedgewick_1();  // SEDGEWICK GAP 1
  void shell_gap_sedgewick_2();  // SEDGEWICK GAP 2
  void shell_gap_gby();          // GONNET & BAEZA-YATES GAP
  void shell_gap_tokuda();       // TOKUDA GAP
  void shell_gap_lee();          // LEE GAP
  void shell_gap_sej();          // SKEAN & EHRENBORG & JAROMCZYK GAP

  //SORTING ALGOS
  void insertion_sort();
  void recur_insertion_sort(int n);
  void shell_sort();

  //TIMER FUNCTIONS
  std::chrono::milliseconds get_elapsed_time() const;
  void restart_timer();
  void pause_timer();

 private:
  // DISPLAYS SCREEN FOR SORTING
  Screen** current_screen;
  Sorting_Class* sort_class;
  sf::RenderWindow* window_ptr;
  int m_selected_button_index;
  int m_selected_button;

  // CONSTANTS
  static constexpr std::size_t c_buttons = 2;
  static constexpr std::size_t c_info = 5;
  static constexpr std::size_t c_options = 3;
  static constexpr std::size_t c_box_vertices = 5;

  // BUTTONS SHAPE, TEXT, NAMES
  std::array<sf::Text, c_buttons> m_buttons_text;
  std::array<std::string, c_buttons> m_buttons_names;
  std::array<sf::RectangleShape, c_buttons> m_buttons_shape;

  // INFORMATION ABOUT VISUALIZATION
  std::array<sf::Text, c_info> m_info_text;
  std::array<std::string, c_info> m_info_names;
  // STATE OF VISUALIZING (FALSE - NOT VISUALIZING, TRUE - VISUALIZING RIGHT NOW)
  bool m_visualizaing;

  // NUMBER OF ELEMENTS, MINIMUM RANGE OF NUMBERS, MAXIMUM RANGE OF NUMBERS
  std::array<int, c_options> m_options;

  // CHOOSED ALGORITHM
  std::string m_algorithm_name;

  // VISUALIZATION BOX
  std::array<sf::Vertex, c_box_vertices> m_viz_box;
  // X_LEFT, Y_TOP, X_RIGHT, Y_BOTTOM, WIDTH, HEIGHT
  std::array<int, c_box_vertices + 1> m_box_pos;

  // SORTING ELEMENTS
  std::vector<int> m_element_number;
  sf::VertexArray m_element_shape;

  std::random_device m_rd;
  std::mt19937 gen;

  // STOP THREAD FLAG
  std::atomic<bool> m_stop_visualizing;
  //SYNC THREADS
  std::variant<std::mutex, std::recursive_mutex> m_mutex;

  //
  std::unordered_map<std::string, std::function<void()>> m_algo_func;

  //SHELL SORT GAPS
  //0 - SHELL, 1 - FRANK & LAZARUS, 2 - HIBBARD, 3 - PAPERNOV & STASEVICH
  //4 - PRATT, 5 - KNUTH, 6 - INCERPI & SADGEWICK, 7 - SEDGEWICK(1), 8 - SEDGEWICK(2)
  //9 - GONNET & BAEZA-YATES, 10 -TOKUDA, 11 - CIURA, 12 - LEE, 13 - SKEAN & EHRENBORG & JAROMCZYK
  int m_selected_shell_gap;
  std::vector<int> m_gaps;

  //TIMER
  std::chrono::milliseconds m_offset{0};  // Sumaryczny czas działania algorytmu
  std::chrono::high_resolution_clock::time_point
      m_last_resume_time;     // Ostatni moment wznowienia
  bool m_is_running = false;  // Czy algorytm jest aktywny
};

#endif
