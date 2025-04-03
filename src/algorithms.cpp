#include <SFML/System/Time.hpp>
#include "sorting_class.h"
#include "visualization.h"

void Visualization::update_rec_style(sf::VertexArray& arr, bool update_pos,
                                     bool update_color, int index, int number,
                                     sf::Color c, bool update_time) {

  std::lock_guard lock(m_mutex);
  if (update_pos)
    update_rectangle_pos(arr, index, number);
  if (update_color)
    update_rectangle_color(arr, index, c);
  if (update_time) {
    m_info_text[4].setString("Duration: " +
                             std::to_string(get_elapsed_time().count()));
  }
}
void Visualization::update_rectangle_pos(sf::VertexArray& arr, int i,
                                         int number) {
  int base = i * 4;
  if (&arr == &m_auxiliary_shape) {
    base += 4;
    if (is_lb_empty(number))
      return;
    if (base + 3 >= m_auxiliary_shape.getVertexCount())
      return;
  }
  double t_i = (static_cast<double>(number) - m_options[1]) /
               (m_options[2] - m_options[1]);
  double H_i = t_i * m_box_pos[5];
  double y_rectangle_top;
  double y_rectangle_bottom;
  if (&arr == &m_auxiliary_shape) {
    y_rectangle_top = (m_box_pos[3] - H_i) / 2;
    y_rectangle_bottom = m_box_pos[3] / 2.0;
  } else {
    y_rectangle_top = m_box_pos[3] - H_i;
    y_rectangle_bottom = m_box_pos[3];
  }
  int n = m_options[0];
  double total_width = m_box_pos[4];
  double max_spacing = 20.0;
  int n_threshold = 50;
  double spacing = 0.0;
  if (n > 1 && n < n_threshold)
    spacing = max_spacing *
              ((n_threshold - n) / static_cast<double>(n_threshold - 1));
  else
    spacing = 0.0;
  double effectiveWidth = (total_width - (n - 1) * spacing) / n;
  double x_rectangle_left = m_box_pos[0] + i * (effectiveWidth + spacing);
  double x_rectangle_right = x_rectangle_left + effectiveWidth;
  arr[base + 0] = sf::Vertex(sf::Vector2f(x_rectangle_left, y_rectangle_top),
                             sf::Color::White);
  arr[base + 1] = sf::Vertex(sf::Vector2f(x_rectangle_right, y_rectangle_top),
                             sf::Color::White);
  arr[base + 2] = sf::Vertex(
      sf::Vector2f(x_rectangle_right, y_rectangle_bottom), sf::Color::White);
  arr[base + 3] = sf::Vertex(sf::Vector2f(x_rectangle_left, y_rectangle_bottom),
                             sf::Color::White);
}

void Visualization::update_rectangle_color(sf::VertexArray& arr, int i,
                                           sf::Color c) {
  if (&arr == &m_auxiliary_shape) {
    if (i < 0 || 2 * i + 1 >= m_auxiliary_shape.getVertexCount() / 4) {
      std::cerr
          << "Error: update_rectangle_color auxiliary index out of range: " << i
          << " (position " << 2 * i + 1 << ")" << std::endl;
      return;
    }
  } else {
    if (i < 0 || i >= m_element_number.size()) {
      std::cerr << "Error: update_rectangle_color index out of range: " << i
                << std::endl;
      return;
    }
  }
  int base;
  if (&arr == &m_auxiliary_shape) {
    base = (2 * i + 1) * 4;
  } else {
    base = i * 4;
  }
  if (base + 3 >= arr.getVertexCount()) {
    std::cerr << "Error: base out of range: " << base << std::endl;
    return;
  }
  for (int k = 0; k < 4; k++) {
    arr[base + k].color = c;
  }
}
void Visualization::insertion_sort() {
  for (int i = 1; i < m_element_number.size(); ++i) {
    if (m_stop_visualizing.load())
      break;
    int key = m_element_number[i];
    update_rec_style(m_element_shape, false, true, i, 0, sf::Color::Green);
    int j = i - 1;
    while (j >= 0 && m_element_number[j] > key) {
      if (m_stop_visualizing.load())
        break;
      update_rec_style(m_element_shape, false, true, j, 0, sf::Color::Red);
      m_element_number[j + 1] = m_element_number[j];
      update_rec_style(m_element_shape, true, false, j + 1,
                       m_element_number[j + 1], sf::Color::White);
      update_rec_style(m_element_shape, false, true, j, 0, sf::Color::White);
      j--;
    }
    if (m_stop_visualizing.load())
      break;
    m_element_number[j + 1] = key;
    update_rec_style(m_element_shape, false, true, i, 0, sf::Color::White);
    update_rec_style(m_element_shape, true, false, j + 1,
                     m_element_number[j + 1], sf::Color::White, true);
  }
  restart_timer();
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}

bool Visualization::recur_insertion_sort(int n) {
  if (m_stop_visualizing.load()) {
    for (int i = 0; i < n; i++)
      update_rec_style(m_element_shape, false, true, i, 0, sf::Color::White);
    return true;
  }
  if (n <= 1)
    return false;
  if (recur_insertion_sort(n - 1))
    return true;
  int last = m_element_number[n - 1];
  int j = n - 2;
  update_rec_style(m_element_shape, false, true, j, 0, sf::Color::Green);
  while (j >= 0 && m_element_number[j] > last) {
    if (m_stop_visualizing.load()) {
      for (int i = 0; i < n; i++)
        update_rec_style(m_element_shape, false, true, i, 0, sf::Color::White);
      return true;
    }
    update_rec_style(m_element_shape, false, true, j, 0, sf::Color::Red);
    m_element_number[j + 1] = m_element_number[j];
    update_rec_style(m_element_shape, true, false, j + 1,
                     m_element_number[j + 1], sf::Color::Red);
    update_rec_style(m_element_shape, false, true, j, 0, sf::Color::White);
    j--;
  }

  m_element_number[j + 1] = last;
  int index_to_update = (j < 0) ? 0 : j;
  update_rec_style(m_element_shape, true, false, j + 1, m_element_number[j + 1],
                   sf::Color::White);
  update_rec_style(m_element_shape, false, true, index_to_update, 0,
                   sf::Color::White, true);
  if (n == m_element_number.size()) {
    restart_timer();
    m_buttons_text[1].setString("Start");
    m_stop_visualizing.store(true);
    m_visualizaing = false;
  }

  return false;
}
void Visualization::shell_gap_shell() {
  for (int i = floor(m_element_number.size() / 2.0); i > 0; i /= 2)
    m_gaps.push_back(i);
}

void Visualization::shell_gap_fl() {
  for (int i = 2 * floor(m_element_number.size() / (2.0 * 2.0)) + 1; i > 0;
       i /= 2)
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
       ((std::pow(3, i) - 1) / 2.0) < ceil(m_element_number.size() / 3.0); i++)
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
      update_rec_style(m_element_shape, false, true, i, 0, sf::Color::Green);
      //   sf::sleep(sf::milliseconds(50));
      for (j = i; j >= gap && m_element_number[j - gap] > temp; j -= gap) {
        if (m_stop_visualizing.load())
          break;
        update_rec_style(m_element_shape, true, false, j - gap,
                         m_element_number[j - gap], sf::Color::White);
        update_rec_style(m_element_shape, false, true, j, 0, sf::Color::Red);
        m_element_number[j] = m_element_number[j - gap];
        //      sf::sleep(sf::milliseconds(50));
        update_rec_style(m_element_shape, true, true, j, m_element_number[j],
                         sf::Color::White);
      }
      //     sf::sleep(sf::milliseconds(50));
      m_element_number[j] = temp;
      update_rec_style(m_element_shape, true, true, j, m_element_number[j],
                       sf::Color::White, true);
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
      update_rec_style(m_element_shape, false, true, low + 1, 0,
                       sf::Color::Green);
      //sf::sleep(sf::milliseconds(1200));

      return low + 1;
    } else {
      update_rec_style(m_element_shape, false, true, low, 0, sf::Color::Green);
      //sf::sleep(sf::milliseconds(1200));

      return low;
    }
  }
  int mid = (low + high) / 2;
  update_rec_style(m_element_shape, false, true, mid, 0, sf::Color::Red);
  //sf::sleep(sf::milliseconds(1200));

  if (item == m_element_number[mid]) {
    update_rec_style(m_element_shape, false, true, mid + 1, 0,
                     sf::Color::Green);
    //sf::sleep(sf::milliseconds(1200));

    return mid + 1;
  }
  if (item > m_element_number[mid])
    return binary_search(item, mid + 1, high);
  return binary_search(item, low, mid - 1);
}

void Visualization::binary_insertion_sort() {
  int i, loc, j, k, selected;
  for (i = 1; i < m_element_number.size(); ++i) {
    if (m_stop_visualizing.load())
      break;
    j = i - 1;
    selected = m_element_number[i];
    update_rec_style(m_element_shape, false, true, i, 0, sf::Color::Green);
    //sf::sleep(sf::milliseconds(1200));

    loc = binary_search(selected, 0, j);
    for (int x = 0; x < m_element_number.size(); x++)
      update_rec_style(m_element_shape, false, true, x, 0, sf::Color::White);
    update_rec_style(m_element_shape, false, true, loc, 0, sf::Color::Green);
    //sf::sleep(sf::milliseconds(1200));

    while (j >= loc) {
      if (m_stop_visualizing.load())
        break;
      m_element_number[j + 1] = m_element_number[j];
      update_rec_style(m_element_shape, true, false, j + 1,
                       m_element_number[j + 1], sf::Color::Green);
      //sf::sleep(sf::milliseconds(1200));
      j--;
    }
    if (m_stop_visualizing.load())
      break;
    m_element_number[j + 1] = selected;
    update_rec_style(m_element_shape, true, false, j + 1,
                     m_element_number[j + 1], sf::Color::Green, true);
    //sf::sleep(sf::milliseconds(1200));
  }
  restart_timer();
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}

bool Visualization::is_lb_empty(int x) {
  return x == m_empty_value;
}

std::vector<int> Visualization::initialize_array(int n) {
  std::vector<int> S(n * 2, m_empty_value);
  for (int i = 0; i < n; i++) {
    S[2 * i + 1] = m_element_number[i];
    update_rec_style(m_element_shape, true, false, i, m_options[1],
                     sf::Color::Green);
    update_rec_style(m_auxiliary_shape, true, false, 2 * i + 1, S[2 * i + 1],
                     sf::Color::Green);
  }
  return S;
}

void Visualization::insert_element(std::vector<int>& S, int p) {
  int s = S[p];
  int x = 0, y = p;
  std::pair<int, int> insertion_range = find_insertion_range(S, s, x, y);
  x = insertion_range.first;
  y = insertion_range.second;
  if (y - x > 1)
    insert_with_space(S, x, y, s);
  else
    insert_with_shift(S, x, y, s);
  S[p] = m_empty_value;
  update_rec_style(m_auxiliary_shape, true, false, p, m_empty_value,
                   sf::Color::Green);
}

std::pair<int, int> Visualization::find_insertion_range(
    const std::vector<int>& S, int s, int x, int y) {
  while (y - x > 1) {
    int c = (x + y) >> 1;
    if (!is_lb_empty(S[c])) {
      if (S[c] < s)
        x = c;
      else
        y = c;
    } else {
      int e = c - 1, f = c + 1;
      while (e >= 0 && is_lb_empty(S[e]))
        e -= 1;
      while (f < S.size() && is_lb_empty(S[f]))
        f += 1;
      if (e >= 0 && !is_lb_empty(S[e]) && S[e] > s)
        y = e;
      else if (f < S.size() && !is_lb_empty(S[f]) && S[f] < s)
        x = f;
      else {
        x = e;
        y = f;
        break;
      }
    }
  }
  return {x, y};
}

void Visualization::insert_with_space(std::vector<int>& S, int x, int y,
                                      int s) {
  S[(x + y) >> 1] = s;
  update_rec_style(m_auxiliary_shape, true, false, (x + y) >> 1, s,
                   sf::Color::Green);
}

void Visualization::insert_with_shift(std::vector<int>& S, int x, int y,
                                      int s) {
  if (!is_lb_empty(S[x])) {
    if (S[x] > s)
      y = x;
    int temp = s;
    int lastIdx = -1;
    while (temp != m_empty_value && y < S.size()) {
      std::swap(S[y], temp);
      lastIdx = y;
      update_rec_style(m_auxiliary_shape, true, false, y, S[y],
                       sf::Color::Green);
      y += 1;
    }

    if (temp != m_empty_value) {
      handle_overflow(S, temp);
    }
  } else {
    S[x] = s;
    update_rec_style(m_auxiliary_shape, true, false, x, S[x], sf::Color::Green);
  }
}

void Visualization::handle_overflow(std::vector<int>& S, int value) {
  for (int k = 0; k < S.size(); k++) {
    if (is_lb_empty(S[k])) {
      S[k] = value;
      update_rec_style(m_auxiliary_shape, true, false, k, S[k],
                       sf::Color::Green);
      break;
    }
  }
}

void Visualization::redistribute_elements(std::vector<int>& S, int max_p) {
  int p = std::min(max_p, static_cast<int>(S.size() - 1));
  int dest_p = p;
  std::vector<int> temp_values;
  for (int s = 0; s <= p; s++) {
    if (!is_lb_empty(S[s])) {
      temp_values.push_back(S[s]);
      S[s] = m_empty_value;
      update_rec_style(m_auxiliary_shape, true, false, s, m_empty_value,
                       sf::Color::Green);
    }
  }
  for (int idx = temp_values.size() - 1; idx >= 0; idx--) {
    if (dest_p >= 0 && dest_p < S.size()) {
      S[dest_p] = temp_values[idx];
      update_rec_style(m_auxiliary_shape, true, false, dest_p, S[dest_p],
                       sf::Color::Green);
      dest_p -= 2;
    }
  }
}

void Visualization::finalize_sort(const std::vector<int>& S) {
  m_element_number.clear();
  std::vector<int> sorted_elements;
  for (const auto& item : S) {
    if (!is_lb_empty(item)) {
      sorted_elements.push_back(item);
    }
  }
  m_element_number = sorted_elements;
  m_box_pos = {50, 125, 1200, 700, 1200 - 50, 700 - 125};
  for (int i = 0; i < m_element_number.size(); i++)
    update_rec_style(m_element_shape, true, false, i, m_element_number[i],
                     sf::Color::Green);
  m_auxiliary_shape.clear();
}

int Visualization::process_iteration(std::vector<int>& S, int n, int a, int b) {
  int max_p = 0;
  update_rec_style(m_element_shape, false, false, 0, 0, sf::Color::Green, true);
  for (int j = a; j < std::min(b, n + 1); j++) {
    int p = 2 * j - 1;
    max_p = std::max(max_p, p);
    if (p >= S.size() || is_lb_empty(S[p]))
      continue;
    insert_element(S, p);
  }
  return max_p;
}

void Visualization::library_sort() {
  int n = m_element_number.size();
  std::vector<int> S = initialize_array(n);
  int m = std::floor(std::log2(n) + 1);
  for (int i = 0; i < m; i++) {
    int a = 1 << (i + 1);
    int b = 1 << (i + 2);
    int max_p = process_iteration(S, n, a, b);
    if (b > n)
      break;
    if (i < m - 1) {
      redistribute_elements(S, max_p);
    }
  }

  finalize_sort(S);
}
