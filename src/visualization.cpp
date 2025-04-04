#include "visualization.h"

#include <thread>

Visualization::Visualization(Screen** screen_ptr, Sorting_Class* sort_class_ptr,
                             sf::RenderWindow* window)
    : current_screen(screen_ptr),
      sort_class(sort_class_ptr),
      window_ptr(window),
      m_gen(m_rd()),
      m_stop_visualizing(false),
      m_offset(std::chrono::milliseconds(0)),
      m_distribution(2) {
  m_visualizaing = false;
  set_styles();
  m_selected_button_index = 1;
  m_selected_button = 1;
  m_element_shape.setPrimitiveType(sf::Quads);
  m_auxiliary_shape.setPrimitiveType(sf::Quads);
  initialize_algorithms();
  m_selected_shell_gap = 0;
  m_empty_value = m_options[1] - 1;
  pause_timer();
}

Visualization::~Visualization() {}

void Visualization::restart_timer() {
  m_offset = std::chrono::milliseconds(0);
  m_last_resume_time = std::chrono::high_resolution_clock::now();
  m_is_running = true;
}
std::chrono::milliseconds Visualization::get_elapsed_time() const {
  if (m_is_running) {
    auto now = std::chrono::high_resolution_clock::now();
    return m_offset + std::chrono::duration_cast<std::chrono::milliseconds>(
                          now - m_last_resume_time);
  }
  return m_offset;
}
void Visualization::pause_timer() {
  if (m_is_running) {
    auto now = std::chrono::high_resolution_clock::now();
    m_offset += std::chrono::duration_cast<std::chrono::milliseconds>(
        now - m_last_resume_time);
    m_is_running = false;
  }
}
void Visualization::draw(sf::RenderWindow& window) {
  std::lock_guard lock(m_mutex);
  for (const auto& x : m_buttons_shape)
    window.draw(x);
  for (const auto& x : m_buttons_text)
    window.draw(x);
  for (const auto& x : m_info_text)
    window.draw(x);
  window.draw(m_viz_box.data(), m_viz_box.size(), sf::LineStrip);
  window.draw(m_element_shape);
  window.draw(m_auxiliary_shape);
}

void Visualization::move_left() {
  if (!m_visualizaing) {
    if (m_selected_button != 0) {
      m_buttons_shape[m_selected_button_index].setOutlineColor(sf::Color::Red);
      m_selected_button_index--;
      m_selected_button = m_selected_button_index;
      m_buttons_shape[m_selected_button].setOutlineColor(sf::Color::Green);
    }
  }
}

void Visualization::move_right() {
  if (!m_visualizaing) {
    if (m_selected_button != c_buttons - 1) {
      m_buttons_shape[m_selected_button_index].setOutlineColor(sf::Color::Red);
      m_selected_button_index++;
      m_selected_button = m_selected_button_index;
      m_buttons_shape[m_selected_button].setOutlineColor(sf::Color::Green);
    }
  }
}
int Visualization::pressed() {
  return m_selected_button;
}
void Visualization::change_option(int selected) {
  if (selected == 0) {
    m_selected_button_index = 1;
    m_selected_button = 1;
    m_buttons_shape[1].setOutlineColor(sf::Color::Green);
    m_buttons_shape[0].setOutlineColor(sf::Color::Red);
    restart_timer();
    pause_timer();
    *current_screen = sort_class;
  } else {
    if (m_visualizaing == true) {
      m_buttons_text[1].setString("Start");
      m_stop_visualizing.store(true);
      m_visualizaing = false;
      pause_timer();
    } else {
      m_buttons_text[1].setString("Stop");
      m_stop_visualizing.store(false);
      try {
        restart_timer();
        std::thread worker_algo(m_algo_func.at(m_algorithm_name));
        worker_algo.detach();
        m_visualizaing = true;
      } catch (const std::out_of_range& e) {
        std::cerr << "Algorithm not found: " << m_algorithm_name << std::endl;
        m_buttons_text[1].setString("Start");
        m_stop_visualizing.store(true);
        m_visualizaing = false;
      }
    }
  }
}
void Visualization::visual() {
  m_element_shape.resize(m_options[0] * 4);
  m_element_number.resize(m_options[0]);
  std::vector<double> boxes_pos;  // x_left, y_top, x_right
  boxes_pos.resize(3);
  if (m_algorithm_name == "Library Sort") {
    m_empty_value = m_options[1] - 1;
    m_auxiliary_shape.resize(4 + m_options[0] * 4);
    m_box_pos = {50, 125, 1200, 700, 1200 - 50, (700 - 125) / 2};
    m_auxiliary_shape[0] =
        sf::Vertex(sf::Vector2f(50, 700 / 2), sf::Color::White);
    m_auxiliary_shape[1] =
        sf::Vertex(sf::Vector2f(1200, 700 / 2), sf::Color::White);
    m_auxiliary_shape[2] =
        sf::Vertex(sf::Vector2f(1200, 700 / 2 + 1), sf::Color::White);
    m_auxiliary_shape[3] =
        sf::Vertex(sf::Vector2f(50, 700 / 2 + 1), sf::Color::White);

  } else {
    m_auxiliary_shape.resize(0);
    m_box_pos = {50, 125, 1200, 700, 1200 - 50, 700 - 125};
  }
  for (int i = 0; i < m_options[0]; i++) {
    int base = i * 4;
    m_element_number[i] = random_number_gen(m_options[1], m_options[2]);
    standardize(boxes_pos, m_element_number[i], i);
    m_element_shape[base + 0] =
        sf::Vertex(sf::Vector2f(boxes_pos[0], boxes_pos[1]), sf::Color::White);
    m_element_shape[base + 1] =
        sf::Vertex(sf::Vector2f(boxes_pos[2], boxes_pos[1]), sf::Color::White);
    m_element_shape[base + 2] =
        sf::Vertex(sf::Vector2f(boxes_pos[2], m_box_pos[3]), sf::Color::White);
    m_element_shape[base + 3] =
        sf::Vertex(sf::Vector2f(boxes_pos[0], m_box_pos[3]), sf::Color::White);
  }
}

void Visualization::set_styles() {
  m_box_pos = {50, 125, 1200, 700, 1200 - 50, 700 - 125};
  m_buttons_names = {"Back", "Start"};
  m_info_names = {""};
  Screen::set_sf_text_style(m_buttons_text, m_buttons_names, 35, 50, 50, false,
                            false);
  Screen::set_sf_text_style(m_info_text, m_info_names, 10, 300, 50, true, false,
                            250, 0, 0, 3);
  Screen::set_sf_text_style(m_info_text, m_info_names, 10, 300, 75, true, false,
                            250, 0, 3, c_info);
  int temp = 0;
  for (int i = 0; i < c_buttons; i++) {
    m_buttons_shape[i].setPosition(50 + temp, 50);
    m_buttons_shape[i].setSize({220, 45});
    m_buttons_shape[i].setOutlineColor(sf::Color::Red);
    m_buttons_shape[i].setOutlineThickness(1.5);
    m_buttons_shape[i].setFillColor(sf::Color::Black);
    m_buttons_text[i].setPosition(
        50 + temp +
            (140 - (static_cast<double>(m_buttons_names[i].length()) * 35) / 2),
        50);
    temp = 930;
  }
  m_buttons_shape[c_buttons - 1].setOutlineColor(sf::Color::Green);
  m_viz_box[0] =
      sf::Vertex(sf::Vector2f(m_box_pos[0], m_box_pos[1]), sf::Color::White);
  m_viz_box[1] =
      sf::Vertex(sf::Vector2f(m_box_pos[2], m_box_pos[1]), sf::Color::White);
  m_viz_box[2] =
      sf::Vertex(sf::Vector2f(m_box_pos[2], m_box_pos[3]), sf::Color::White);
  m_viz_box[3] =
      sf::Vertex(sf::Vector2f(m_box_pos[0], m_box_pos[3]), sf::Color::White);
  m_viz_box[4] =
      sf::Vertex(sf::Vector2f(m_box_pos[0], m_box_pos[1]), sf::Color::White);
}

void Visualization::set_options(std::size_t n_elements, int min_val,
                                int max_val, std::string algo_name) {
  m_options[0] = n_elements;
  m_options[1] = min_val;
  m_options[2] = max_val;
  m_algorithm_name = algo_name;
  m_info_text[0].setString("Algorithm: " + m_algorithm_name);
  m_info_text[1].setString("Number of elements: " + std::to_string(n_elements));
  m_info_text[2].setString("Min range: " + std::to_string(min_val));
  m_info_text[3].setString("Max range: " + std::to_string(max_val));
  m_info_text[4].setString("Duration: " +
                           std::to_string(get_elapsed_time().count()));
}

int Visualization::random_number_gen(int min_val, int max_val) {
  /*switch (m_distribution) {
    case 0: {
      std::uniform_int_distribution<> distrib(min_val, max_val);
      return distrib(m_gen);
    }
    case 1: {
      std::binomial_distribution<> distrib(max_val, 0.5);
      return distrib(m_gen);
    }
    case 2: {
      std::negative_binomial_distribution<> distrib(5, 0.75);
      return distrib(m_gen);
      std::poisson_distribution<> d(4);
    }
    case 3: {
      std::poisson_distribution<> distrib(5);
      return distrib(m_gen);
    }
    default:
      throw std::invalid_argument("Invalid distribution type");
  }*/
  std::uniform_int_distribution<> distrib(min_val, max_val);
  return distrib(m_gen);
  //return 0;
}

void Visualization::standardize(std::vector<double>& box_pos, int number,
                                int i) {
  box_pos.erase(box_pos.begin(), box_pos.end());
  double t_i = (static_cast<double>(number) - m_options[1]) /
               (m_options[2] - m_options[1]);
  double H_i = t_i * m_box_pos[5];
  double y_rectangle_top = m_box_pos[3] - H_i;
  double total_width = m_box_pos[4];
  int n = m_options[0];
  double maxSpacing = 20.0;
  int n_threshold = 50;
  double spacing = 0.0;

  if (n > 1 && n < n_threshold) {
    spacing =
        maxSpacing * (static_cast<double>(n_threshold - n) / (n_threshold - 2));
  } else
    spacing = 0.0;
  double effectiveWidth = (total_width - (n - 1) * spacing) / n;
  double x_rectangle_left = m_box_pos[0] + i * (effectiveWidth + spacing);
  double x_rectangle_right = x_rectangle_left + effectiveWidth;

  box_pos.push_back(x_rectangle_left);
  box_pos.push_back(y_rectangle_top);
  box_pos.push_back(x_rectangle_right);
  restart_timer();
}

void Visualization::initialize_algorithms() {
  m_algo_func["Insertion Sort"] = [this]() {
    insertion_sort();
  };
  m_algo_func["Recursive Insertion Sort"] = [this]() {
    recur_insertion_sort(m_options[0]);
  };
  m_algo_func["Shell Sort"] = [this]() {
    shell_sort();
  };
  m_algo_func["Binary Insertion Sort"] = [this]() {
    binary_insertion_sort();
  };
  m_algo_func["Library Sort"] = [this]() {
    library_sort();
  };
}
