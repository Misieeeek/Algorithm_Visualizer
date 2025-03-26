/*#include <unistd.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <mutex>
#include <string>
#include <variant>*/
#include "sorting_class.h"
#include "visualization.h"

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
      m_info_text[4].setString("Duration: " +
                               std::to_string(get_elapsed_time().count()));
    }
  }
  restart_timer();
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
    m_info_text[4].setString("Duration: " +
                             std::to_string(get_elapsed_time().count()));
  }
  if (n == m_element_number.size()) {
    restart_timer();
    m_buttons_text[1].setString("Start");
    m_stop_visualizing.store(true);
    m_visualizaing = false;
  }
}

void Visualization::shell_gap_shell() {
  for (int i = floor(m_element_number.size() / 2); i > 0; i /= 2)
    m_gaps.push_back(i);
}

void Visualization::shell_gap_fl() {
  for (int i = 2 * floor(m_element_number.size() / (2 * 2)) + 1; i > 0; i /= 2)
    m_gaps.push_back(i);
}

void Visualization::shell_gap_hibbard() {
  for (int i = 1; std::pow(2, i) - 1 < m_element_number.size(); i++)
    m_gaps.push_back(std::pow(2, i) - 1);
}

void Visualization::shell_gap_ps() {
  m_gaps.push_back(1);
  for (int i = 1; std::pow(2, i) + 1 < m_element_number.size(); i++)
    m_gaps.push_back(std::pow(2, i) + 1);
}

void Visualization::shell_gap_pratt() {
  m_gaps.push_back(1);
  {
    int i2 = 0, i3 = 0;
    while (m_gaps.back() < m_element_number.size()) {
      int n2 = 2 * m_gaps[i2];
      int n3 = 3 * m_gaps[i3];
      int next_val = std::min(n2, n3);
      if (next_val >= m_element_number.size())
        break;
      m_gaps.push_back(next_val);
      if (next_val == n2)
        i2++;
      if (next_val == n3)
        i3++;
    }
  }
}
void Visualization::shell_gap_knuth() {
  for (int i = 1;
       ((std::pow(3, i) - 1) / 2) < ceil(m_element_number.size() / 3); i++)
    m_gaps.push_back(((std::pow(3, i) - 1) / 2));
}

void Visualization::shell_gap_is() {
  std::vector<int> temp = {1,     3,      7,      21,     48,    112,
                           336,   861,    1968,   4592,   13776, 33936,
                           86961, 198768, 463792, 1391376};
  int i = 0;
  while (temp[i] < m_element_number.size()) {
    m_gaps.push_back(temp[i]);
    i++;
  }
}
void Visualization::shell_gap_sedgewick_1() {
  m_gaps.push_back(1);
  for (int i = 1;
       (std::pow(4, i) + 3 * std::pow(2, i - 1) + 1) < m_element_number.size();
       i++)
    m_gaps.push_back(std::pow(4, i) + 3 * std::pow(2, i - 1) + 1);
}

void Visualization::shell_gap_sedgewick_2() {
  m_gaps.push_back(1);
  for (int i = 1; m_gaps.back() < m_element_number.size(); i++) {
    int candidate = 0;
    if (i % 2 == 0)
      candidate =
          static_cast<int>(9 * (std::pow(2, i) - std::pow(2, i / 2)) + 1);
    else
      candidate = static_cast<int>(8 * std::pow(2, i) -
                                   6 * std::pow(2, ((i + 1) / 2)) + 1);
    if (candidate < m_element_number.size())
      m_gaps.push_back(candidate);
    else
      break;
  }
}
void Visualization::shell_gap_gby() {
  int gap = (5 * m_element_number.size() - 1) / 11;
  while (gap > 0) {
    m_gaps.push_back(gap);
    gap = (5 * gap - 1) / 11;
  }
}
void Visualization::shell_gap_tokuda() {
  for (int i = 1; std::ceil((1.0 / 5) * (9 * std::pow(9.0 / 4, i - 1) - 4)) <
                  m_element_number.size();
       i++)
    m_gaps.push_back(std::ceil((1.0 / 5) * (9 * std::pow(9.0 / 4, i - 1) - 4)));
}
void Visualization::shell_gap_lee() {
  double y = 2.243609061420001;
  for (int i = 1;
       std::ceil((std::pow(y, i) - 1) / (y - 1)) < m_element_number.size(); i++)
    m_gaps.push_back(std::ceil((std::pow(y, i) - 1) / (y - 1)));
}
void Visualization::shell_gap_sej() {
  m_gaps.push_back(1);
  for (int i = 0; std::floor(4.0816 * std::pow(8.5714, (i / 2.2449))) <
                  m_element_number.size();
       i++)
    m_gaps.push_back(std::floor(4.0816 * std::pow(8.5714, (i / 2.2449))));
}
void Visualization::set_shell_gaps() {
  m_gaps.clear();
  switch (m_selected_shell_gap) {
    case 0:  //SHELL
      shell_gap_shell();
      break;
    case 1:  // FRANK & LAZARUS
      shell_gap_fl();
      break;
    case 2:  // HIBBARD
      shell_gap_hibbard();
      std::reverse(m_gaps.begin(), m_gaps.end());
      break;
    case 3:  // PAPERNOV & STASEVICH
      shell_gap_ps();
      std::reverse(m_gaps.begin(), m_gaps.end());
      break;
    case 4:  // PRATT
      shell_gap_pratt();
      std::reverse(m_gaps.begin(), m_gaps.end());
      break;
    case 5:  // KNUTH
      shell_gap_knuth();
      std::reverse(m_gaps.begin(), m_gaps.end());
      break;
    case 6:  // INCERPI & SEDGEWICK
      shell_gap_is();
      std::reverse(m_gaps.begin(), m_gaps.end());
      break;
    case 7:  // SEDGEWICK (1)
      shell_gap_sedgewick_1();
      std::reverse(m_gaps.begin(), m_gaps.end());
      break;
    case 8:  // SEDGEWICK (2)
      shell_gap_sedgewick_2();
      std::reverse(m_gaps.begin(), m_gaps.end());
      break;
    case 9:  // GONNET & BAEZA-YATES
      shell_gap_gby();
      break;
    case 10:  // TOKUDA
      shell_gap_tokuda();
      std::reverse(m_gaps.begin(), m_gaps.end());
      break;
    case 11:  // CIURA
      m_gaps.insert(m_gaps.end(), {701, 301, 132, 57, 23, 10, 4, 1});
      break;
    case 12:  // LEE
      shell_gap_lee();
      std::reverse(m_gaps.begin(), m_gaps.end());
      break;
    case 13:  // SKEAN & EHRENBORG & JAROMCZYK
      shell_gap_sej();
      std::reverse(m_gaps.begin(), m_gaps.end());
      break;
    default:
      std::cerr << "Error: selected shell gap not found: "
                << m_selected_shell_gap << std::endl;
      break;
  }
}

void Visualization::shell_sort() {
  m_selected_shell_gap = sort_class->get_shell_gap();
  set_shell_gaps();
  for (auto gap : m_gaps) {
    if (m_stop_visualizing.load())
      break;
    for (int i = gap; i < m_element_number.size(); i++) {
      if (m_stop_visualizing.load())
        break;
      int temp = m_element_number[i];
      int j;
      {
        std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
        update_rectangle_color(i, sf::Color::Green);
      }
      //   sf::sleep(sf::milliseconds(50));
      for (j = i; j >= gap && m_element_number[j - gap] > temp; j -= gap) {
        if (m_stop_visualizing.load())
          break;
        {
          std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
          update_rectangle_pos(j - gap, m_element_number[j - gap]);
          update_rectangle_color(j, sf::Color::Red);
        }
        m_element_number[j] = m_element_number[j - gap];
        //      sf::sleep(sf::milliseconds(50));
        {
          std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
          update_rectangle_pos(j, m_element_number[j]);
          update_rectangle_color(j, sf::Color::White);
        }
      }
      //     sf::sleep(sf::milliseconds(50));
      m_element_number[j] = temp;
      {
        std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
        update_rectangle_pos(j, m_element_number[j]);
        update_rectangle_color(j, sf::Color::White);
        m_info_text[4].setString("Duration: " +
                                 std::to_string(get_elapsed_time().count()));
      }
      //      sf::sleep(sf::milliseconds(50));
    }
  }
  restart_timer();
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}

int Visualization::binary_search(int item, int low, int high) {
  if (high <= low) {
    if (item > m_element_number[low]) {
      {
        check_mutex_type();
        update_rectangle_color(low + 1, sf::Color::Green);
      }
      sf::sleep(sf::milliseconds(2000));

      return low + 1;
    } else {
      {
        check_mutex_type();
        update_rectangle_color(low, sf::Color::Green);
      }
      sf::sleep(sf::milliseconds(2000));

      return low;
    }
  }
  int mid = (low + high) / 2;
  {
    check_mutex_type();
    update_rectangle_color(mid, sf::Color::Red);
  }
  sf::sleep(sf::milliseconds(2000));

  if (item == m_element_number[mid]) {
    {
      check_mutex_type();
      update_rectangle_color(mid + 1, sf::Color::Green);
    }
    sf::sleep(sf::milliseconds(2000));

    return mid + 1;
  }
  if (item > m_element_number[mid])
    return binary_search(item, mid + 1, high);
  return binary_search(item, low, mid - 1);
}

void Visualization::binary_insertion_sort() {
  int i, loc, j, k, selected;
  for (i = 1; i < m_element_number.size(); ++i) {
    j = i - 1;
    selected = m_element_number[i];
    {
      std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
      update_rectangle_color(i, sf::Color::Green);
    }
    sf::sleep(sf::milliseconds(2000));

    loc = binary_search(selected, 0, j);
    {
      std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
      for (int x = 0; x < m_element_number.size(); x++)
        update_rectangle_color(x, sf::Color::White);
      update_rectangle_color(loc, sf::Color::Green);
    }
    sf::sleep(sf::milliseconds(2000));

    while (j >= loc) {
      m_element_number[j + 1] = m_element_number[j];
      {
        std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
        update_rectangle_pos(j + 1, m_element_number[j + 1]);
      }
      sf::sleep(sf::milliseconds(2000));

      j--;
    }
    m_element_number[j + 1] = selected;
    {
      std::lock_guard<std::mutex> lock(std::get<std::mutex>(m_mutex));
      update_rectangle_pos(j + 1, m_element_number[j + 1]);
    }
    sf::sleep(sf::milliseconds(2000));
  }
  restart_timer();
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}
