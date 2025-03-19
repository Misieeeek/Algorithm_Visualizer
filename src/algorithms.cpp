#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <chrono>
#include <mutex>
#include <variant>
#include "visualizer.h"

void Visualization::update_rectangle_pos(int i, int number) {
  int base = i * 4;

  double t_i = (static_cast<double>(number) - m_options[1]) /
               (m_options[2] - m_options[1]);
  double H_i = t_i * m_box_pos[5];
  double y_rectangle_top = m_box_pos[3] - H_i;

  int n = m_options[0];
  double total_width = m_box_pos[4];
  double maxSpacing = 20.0;
  int n_threshold = 50;
  double spacing = 0.0;
  if (n > 1 && n < n_threshold) {
    spacing =
        maxSpacing * ((n_threshold - n) / static_cast<double>(n_threshold - 1));
  } else {
    spacing = 0.0;
  }
  double effectiveWidth = (total_width - (n - 1) * spacing) / n;
  double x_rectangle_left = m_box_pos[0] + i * (effectiveWidth + spacing);
  double x_rectangle_right = x_rectangle_left + effectiveWidth;
  m_element_shape[base + 0] = sf::Vertex(
      sf::Vector2f(x_rectangle_left, y_rectangle_top), sf::Color::White);
  m_element_shape[base + 1] = sf::Vertex(
      sf::Vector2f(x_rectangle_right, y_rectangle_top), sf::Color::White);
  m_element_shape[base + 2] = sf::Vertex(
      sf::Vector2f(x_rectangle_right, m_box_pos[3]), sf::Color::White);
  m_element_shape[base + 3] = sf::Vertex(
      sf::Vector2f(x_rectangle_left, m_box_pos[3]), sf::Color::White);
}

void Visualization::update_rectangle_color(int i, sf::Color c) {
  if (i < 0 || i >= m_element_number.size()) {
    std::cerr << "Error: update_rectangle_color index out of range: " << i
              << std::endl;
    return;
  }
  int base = i * 4;
  if (base + 3 >= m_element_shape.getVertexCount()) {
    std::cerr << "Error: base out of range: " << base << std::endl;
    return;
  }

  for (int k = 0; k < 4; k++) {
    m_element_shape[base + k].color = c;
  }
}

void Visualization::check_mutex_type() {
  if (std::holds_alternative<std::recursive_mutex>(m_mutex))
    std::lock_guard<std::recursive_mutex> lock(
        std::get<std::recursive_mutex>(m_mutex));
  else if (std::holds_alternative<std::mutex>(m_mutex))
    std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
}

void Visualization::insertion_sort() {
  for (int i = 1; i < m_element_number.size(); ++i) {
    if (m_stop_visualizing.load())
      break;
    int key = m_element_number[i];
    {
      std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
      update_rectangle_color(i, sf::Color::Green);
    }
    int j = i - 1;
    while (j >= 0 && m_element_number[j] > key) {
      if (m_stop_visualizing.load())
        break;
      {
        std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
        update_rectangle_color(j, sf::Color::Red);
      }
      m_element_number[j + 1] = m_element_number[j];
      {
        std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
        update_rectangle_pos(j + 1, m_element_number[j + 1]);
        update_rectangle_color(j, sf::Color::White);
      }
      j--;
    }
    if (m_stop_visualizing.load())
      break;
    m_element_number[j + 1] = key;
    {
      std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
      update_rectangle_color(i, sf::Color::White);
      update_rectangle_pos(j + 1, m_element_number[j + 1]);
    }
  }
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}
void Visualization::recur_insertion_sort(int n) {
  if (m_stop_visualizing.load()) {
    for (int i = 0; i < n; i++)
      update_rectangle_color(i, sf::Color::White);
    return;
  }
  if (n <= 1)
    return;

  recur_insertion_sort(n - 1);
  int last = m_element_number[n - 1];
  int j = n - 2;
  {
    check_mutex_type();
    update_rectangle_color(j, sf::Color::Green);
  }
  while (j >= 0 && m_element_number[j] > last) {
    if (m_stop_visualizing.load()) {
      for (int i = 0; i < n; i++)
        update_rectangle_color(i, sf::Color::White);
      return;
    }
    {
      check_mutex_type();
      update_rectangle_color(j, sf::Color::Red);
    }
    m_element_number[j + 1] = m_element_number[j];
    {
      check_mutex_type();
      update_rectangle_pos(j + 1, m_element_number[j + 1]);
      update_rectangle_color(j, sf::Color::White);
    }
    j--;
  }
  m_element_number[j + 1] = last;
  {
    check_mutex_type();
    int indexToUpdate = (j < 0) ? 0 : j;
    update_rectangle_color(indexToUpdate, sf::Color::White);
    update_rectangle_pos(j + 1, m_element_number[j + 1]);
  }
  if (n == m_element_number.size()) {
    m_buttons_text[1].setString("Start");
    m_stop_visualizing.store(true);
    m_visualizaing = false;
  }
}
