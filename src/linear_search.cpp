#include <algorithm>
#include "visualization.h"
#include "visualization_options.h"

void Visualization::linear_search() {
  for (int i = 0; i < m_element_number.size() - 1; i++) {
    if (m_stop_visualizing.load())
      break;
    if (m_element_number[i] != m_options[3]) {
      update_rec_style(m_element_shape, false, true, i, 0, sf::Color::Red);
    } else {
      update_rec_style(m_element_shape, false, true, i, 0, sf::Color::Green);
      break;
    }
    update_rec_style(m_element_shape, false, true, i, 0, sf::Color::White);
  }
  restart_timer();
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}

void Visualization::binary_search() {
  std::cout << m_options[3] << "\n";
  std::sort(m_element_number.begin(), m_element_number.end());
  for (int i = 0; i < m_element_number.size(); i++)
    update_rec_style(m_element_shape, true, false, i, m_element_number[i],
                     sf::Color::White);
  int p = 0;
  int q = m_element_number.size();
  int mid = (p + q) / 2;
  while (p != q) {
    if (m_stop_visualizing.load())
      break;
    if (m_options[3] > m_element_number[mid])
      p = mid + 1;
    else if (m_options[3] < m_element_number[mid])
      q = mid - 1;
    else {
      update_rec_style(m_element_shape, false, true, mid, 0, sf::Color::Green);
      break;
    }
    mid = (p + q) / 2;
  }
  restart_timer();
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}
