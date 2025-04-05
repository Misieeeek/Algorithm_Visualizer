#include "sorting_class.h"
#include "visualization.h"

void Visualization::selection_sort() {
  for (int i = 0; i < m_element_number.size(); i++) {
    int min_index = i;
    for (int j = i + 1; j < m_element_number.size(); j++) {
      if (m_element_number[j] < m_element_number[min_index]) {
        min_index = j;
        update_rec_style(m_element_shape, false, true, j, 0, sf::Color::Red);
      }
    }
    if (min_index != i) {
      std::swap(m_element_number[i], m_element_number[min_index]);
      update_rec_style(m_element_shape, true, true, i, m_element_number[i],
                       sf::Color::Green, true);
      update_rec_style(m_element_shape, true, true, min_index,
                       m_element_number[min_index], sf::Color::Green, true);
    }
    update_rec_style(m_element_shape, false, true, i, 0, sf::Color::White,
                     true);
    update_rec_style(m_element_shape, false, true, min_index, 0,
                     sf::Color::White, true);
  }
  restart_timer();
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}
