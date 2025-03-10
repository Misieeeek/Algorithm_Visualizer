#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include "visualizer.h"

void Visualization::update_rectangle_pos(int i, int number) {

  int base = i * 4;
  double t_i = ((static_cast<double>(number) - m_options[1]) /
                (m_options[2] - m_options[1]));
  double H_i = t_i * m_box_pos[5];
  double y_rectangle_top = m_box_pos[3] - H_i;
  double w = static_cast<double>(m_box_pos[4]) / m_options[0];
  double x_rectangle_left = m_box_pos[0] + i * w;
  double x_rectangle_right = x_rectangle_left + w;

  std::array<double, 3> temp = {x_rectangle_left, y_rectangle_top,
                                x_rectangle_right};
  m_element_shape[base + 0] =
      sf::Vertex(sf::Vector2f(temp[0], temp[1]), sf::Color::White);
  m_element_shape[base + 1] =
      sf::Vertex(sf::Vector2f(temp[2], temp[1]), sf::Color::White);
  m_element_shape[base + 2] =
      sf::Vertex(sf::Vector2f(temp[2], m_box_pos[3]), sf::Color::White);
  m_element_shape[base + 3] =
      sf::Vertex(sf::Vector2f(temp[0], m_box_pos[3]), sf::Color::White);
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
      //sf::sleep(sf::microseconds(1));
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
