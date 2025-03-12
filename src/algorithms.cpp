#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
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
  int base = i * 4;
  for (int j = 0; j < 4; j++)
    m_element_shape[base + j].color = c;
}
void Visualization::insertion_sort() {
  for (int i = 1; i < m_element_number.size(); ++i) {
    if (m_stop_visualizing.load())
      break;
    int key = m_element_number[i];
    update_rectangle_color(i, sf::Color::Green);
    //sf::sleep(sf::microseconds(1));
    int j = i - 1;
    while (j >= 0 && m_element_number[j] > key) {
      if (m_stop_visualizing.load())
        break;
      update_rectangle_color(j, sf::Color::Red);
      m_element_number[j + 1] = m_element_number[j];
      //sf::sleep(sf::microseconds(500000));
      update_rectangle_pos(j + 1, m_element_number[j + 1]);
      update_rectangle_color(j, sf::Color::White);
      j = j - 1;
      // sf::sleep(sf::microseconds(1));
    }
    if (m_stop_visualizing.load())
      break;
    m_element_number[j + 1] = key;
    update_rectangle_color(i, sf::Color::White);
    update_rectangle_pos(j + 1, m_element_number[j + 1]);
    //sf::sleep(sf::microseconds(1));
  }
}
