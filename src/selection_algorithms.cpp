#include <algorithm>
#include <bitset>
#include <execution>
#include <functional>
#include <memory>
#include <queue>
#include "SFML/System/Sleep.hpp"
#include "SFML/System/Time.hpp"
#include "visualization.h"
#include "visualization_options.h"

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

int Visualization::count_trailing_zeros(int x) {
  if (x == 0)
    return 32;
  int count = 0;
  while ((x & 1) == 0) {
    x >>= 1;
    count++;
  }
  return count;
}

std::vector<int> Visualization::leonardo(int k) {
  std::vector<int> leo;
  leo.push_back(1);
  leo.push_back(1);
  for (int i = 2; i <= k; i++)
    leo.push_back(leo[i - 1] + leo[i - 2] + 1);
  return leo;
}

void Visualization::sift(int pshift, int head, std::vector<int>& leo) {
  int val = m_element_number[head];
  while (pshift > 1) {
    int rt = head - 1;
    int lf = head - 1 - leo[pshift - 2];
    if (val >= m_element_number[lf] && val >= m_element_number[rt])
      break;
    if (m_element_number[lf] >= m_element_number[rt]) {
      update_rec_style(m_element_shape, true, true, head, m_element_number[lf],
                       sf::Color::Red);
      m_element_number[head] = m_element_number[lf];
      update_rec_style(m_element_shape, true, true, head, m_element_number[lf],
                       sf::Color::White);
      head = lf;
      pshift -= 1;
    } else {
      update_rec_style(m_element_shape, true, true, head, m_element_number[rt],
                       sf::Color::Green);
      m_element_number[head] = m_element_number[rt];
      update_rec_style(m_element_shape, true, true, head, m_element_number[rt],
                       sf::Color::White);
      head = rt;
      pshift -= 2;
    }
  }
  update_rec_style(m_element_shape, true, true, head, val, sf::Color::White);
  m_element_number[head] = val;
}

void Visualization::trinkle(int p, int pshift, int head, bool is_trusty,
                            std::vector<int>& leo) {
  update_rec_style(m_element_shape, false, false, 0, 0, sf::Color::White, true);
  int val = m_element_number[head];
  while (p != 1) {
    int stepson = head - leo[pshift];
    if (stepson < 0 || stepson >= m_element_number.size())
      break;
    if (m_element_number[stepson] <= val)
      break;
    if (!is_trusty && pshift > 1) {
      int rt = head - 1;
      int lf = head - 1 - leo[pshift - 2];
      if (rt < 0 || rt >= m_element_number.size() || lf < 0 ||
          lf >= m_element_number.size())
        break;
      if (m_element_number[rt] >= m_element_number[stepson] ||
          m_element_number[lf] >= m_element_number[stepson])
        break;
    }
    update_rec_style(m_element_shape, true, false, head,
                     m_element_number[stepson], sf::Color::White);
    m_element_number[head] = m_element_number[stepson];
    head = stepson;
    int trail = count_trailing_zeros(p & ~1);
    p >>= trail;
    pshift += trail;
    is_trusty = false;
  }
  if (!is_trusty) {
    update_rec_style(m_element_shape, true, false, head, val, sf::Color::White);
    m_element_number[head] = val;
    sift(pshift, head, leo);
  }
}

void Visualization::smooth_sort() {
  if (m_element_number.size() == 0)
    return;
  int k = 1;
  std::vector<int> leo;
  while (leonardo(k).back() < m_element_number.size()) {
    k++;
  }
  leo = leonardo(k);
  int head = 0;
  int p = 1;
  int pshift = 1;
  int hi = m_element_number.size();
  while (head < hi) {
    if ((p & 3) == 3) {
      sift(pshift, head, leo);
      p >>= 2;
      pshift += 2;
    } else {
      if (leo[pshift - 1] >= hi - head) {
        trinkle(p, pshift, head, false, leo);
      } else {
        sift(pshift, head, leo);
      }
      if (pshift == 1) {
        p <<= 1;
        pshift--;
      } else {
        p <<= (pshift - 1);
        pshift = 1;
      }
    }
    p |= 1;
    head++;
  }
  trinkle(p, pshift, head - 1, false, leo);
  while (pshift != 1 || p != 1) {
    if (pshift <= 1) {
      int trail = count_trailing_zeros(p & ~1);
      p >>= trail;
      pshift += trail;
    } else {
      p <<= 2;
      p ^= 7;
      pshift -= 2;
      trinkle(p >> 1, pshift + 1, head - leo[pshift] - 1, true, leo);
      trinkle(p, pshift, head - 1, true, leo);
    }
    head--;
  }
  restart_timer();
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}

void Visualization::heapify(int n, int i) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  if (l < n && m_element_number[l] > m_element_number[largest])
    largest = l;
  if (r < n && m_element_number[r] > m_element_number[largest])
    largest = r;
  if (largest != i) {
    update_rec_style(m_element_shape, false, true, i, m_element_number[i],
                     sf::Color::Red);
    update_rec_style(m_element_shape, false, true, largest,
                     m_element_number[largest], sf::Color::Red);
    std::swap(m_element_number[i], m_element_number[largest]);
    update_rec_style(m_element_shape, true, true, i, m_element_number[i],
                     sf::Color::White);
    update_rec_style(m_element_shape, true, true, largest,
                     m_element_number[largest], sf::Color::White);
    heapify(n, largest);
  }
}

void Visualization::heap_sort() {
  for (int i = m_element_number.size() / 2 - 1; i >= 0; i--)
    heapify(m_element_number.size(), i);
  for (int i = m_element_number.size() - 1; i > 0; i--) {
    update_rec_style(m_element_shape, false, true, 0, m_element_number[0],
                     sf::Color::Red);
    update_rec_style(m_element_shape, false, true, i, m_element_number[i],
                     sf::Color::Red);
    std::swap(m_element_number[0], m_element_number[i]);
    update_rec_style(m_element_shape, true, true, 0, m_element_number[0],
                     sf::Color::White);
    update_rec_style(m_element_shape, true, true, i, m_element_number[i],
                     sf::Color::White, true);
    heapify(i, 0);
  }
  restart_timer();
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}

void Visualization::cartesian_inorder(std::shared_ptr<Node> root) {
  using node_pair = std::pair<int, std::shared_ptr<Node>>;
  std::priority_queue<node_pair, std::vector<node_pair>,
                      std::greater<node_pair>>
      prio_queue;

  prio_queue.push(std::make_pair(root->data, root));
  int i = 0;
  while (!prio_queue.empty()) {
    if (m_stop_visualizing.load())
      break;
    node_pair popped_pair = prio_queue.top();
    prio_queue.pop();
    auto current = popped_pair.second;
    if (!current)
      continue;

    if (current->left != nullptr)
      prio_queue.push(std::make_pair(current->left->data, current->left));

    if (current->right != nullptr)
      prio_queue.push(std::make_pair(current->right->data, current->right));

    m_element_number[i] = current->data;
    // sf::sleep(sf::seconds(1));
    update_rec_style(m_element_shape, true, false, i, m_element_number[i],
                     sf::Color::White);
    update_rec_style(m_auxiliary_shape, false, true, current->index, 0,
                     sf::Color::Black, true);
    i++;
  }
}

void Visualization::cartesian_tree_sort() {
  if (m_element_number.size() == 0)
    return;
  std::shared_ptr<Node> root = build_cartesian_tree();
  cartesian_inorder(root);
  restart_timer();
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}

std::shared_ptr<Visualization::Node> Visualization::build_cartesian_tree_util(
    int root, std::vector<int>& parent, std::vector<int>& left_child,
    std::vector<int>& right_child) {
  if (root == -1)
    return NULL;

  std::unique_ptr<Node> temp = std::make_unique<Node>();
  temp->data = m_element_number[root];
  temp->index = root;
  update_rec_style(m_auxiliary_shape, true, false, root, m_element_number[root],
                   sf::Color::White, true);
  temp->left = build_cartesian_tree_util(left_child[root], parent, left_child,
                                         right_child);
  temp->right = build_cartesian_tree_util(right_child[root], parent, left_child,
                                          right_child);

  return temp;
}

std::shared_ptr<Visualization::Node> Visualization::build_cartesian_tree() {
  size_t n = m_element_number.size();
  if (n == 0)
    return nullptr;

  std::vector<int> parent(n, -1);
  std::vector<int> left_child(n, -1);
  std::vector<int> right_child(n, -1);

  int root = 0, last;

  for (int i = 1; i <= n - 1; i++) {
    if (m_stop_visualizing.load())
      break;
    last = i - 1;
    right_child[i] = -1;
    while (m_element_number[last] >= m_element_number[i] && last != root)
      last = parent[last];

    if (m_element_number[last] >= m_element_number[i]) {
      parent[root] = i;
      left_child[i] = root;
      root = i;
    }

    else if (right_child[last] == -1) {
      right_child[last] = i;
      parent[i] = last;
      left_child[i] = -1;
    }

    else {
      parent[right_child[last]] = i;
      left_child[i] = right_child[last];
      right_child[last] = i;
      parent[i] = last;
    }
  }
  parent[root] = -1;
  return (build_cartesian_tree_util(root, parent, left_child, right_child));
}

void Visualization::tournament_sort() {
  if (m_element_number.empty() || m_element_number.size() == 1)
    return;
  int value;
  size_t n = m_element_number.size();
  std::vector<int> temp(2 * n);
  create_tournament_tree(value, temp, n);
  for (int i = 0; i < m_element_number.size(); i++) {
    if (m_stop_visualizing.load())
      break;
    m_element_number[i] = value;
    update_rec_style(m_element_shape, true, false, i, m_element_number[i],
                     sf::Color::Red);
    recreate_tournament_tree(value, temp, n);
  }
  for (int i = 0; i < temp.size(); i++)
    update_rec_style(m_auxiliary_shape, true, false, i, m_options[1],
                     sf::Color::White);
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}

int Visualization::tournament_winner(int pos1, int pos2, std::vector<int>& temp,
                                     size_t n) {
  int u = pos1 >= n ? pos1 : temp[pos1];
  int v = pos2 >= n ? pos2 : temp[pos2];
  if (temp[u] <= temp[v])
    return u;
  return v;
}

void Visualization::create_tournament_tree(int& value, std::vector<int>& temp,
                                           size_t n) {
  for (int i = 0; i < n; i++) {
    if (m_stop_visualizing.load())
      break;
    temp[n + i] = m_element_number[i];
    update_rec_style(m_auxiliary_shape, true, false, n + i, temp[n + i],
                     sf::Color::White, true);
  }

  for (int i = 2 * n - 1; i > 1; i -= 2) {
    if (m_stop_visualizing.load())
      break;
    int k = i / 2;
    int j = i - 1;
    temp[k] = tournament_winner(i, j, temp, n);
    if (!(temp[temp[k]] > m_options[2]))
      update_rec_style(m_auxiliary_shape, true, true, k, temp[temp[k]],
                       sf::Color::White, true);
  }

  value = temp[temp[1]];
  temp[temp[1]] = INT_MAX;
}
void Visualization::recreate_tournament_tree(int& value, std::vector<int>& temp,
                                             size_t n) {
  int i = temp[1];
  while (i > 1) {
    if (m_stop_visualizing.load())
      break;
    int j, k = i / 2;
    if (i % 2 == 0 && i < 2 * n - 1)
      j = i + 1;
    else
      j = i - 1;

    temp[k] = tournament_winner(i, j, temp, n);
    if (!(temp[temp[k]] > m_options[2]))
      update_rec_style(m_auxiliary_shape, true, true, k, temp[temp[k]],
                       sf::Color::White, true);
    i = k;
  }

  value = temp[temp[1]];
  temp[temp[1]] = INT_MAX;
}

void Visualization::cycle_sort() {
  size_t n = m_element_number.size();
  if (n == 0 || n == 1)
    return;

  int writes = 0;
  for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
    int item = m_element_number[cycle_start];

    int pos = cycle_start;
    for (int i = cycle_start + 1; i < n; i++)
      if (m_element_number[i] < item)
        pos++;

    if (pos == cycle_start)
      continue;

    while (item == m_element_number[pos])
      pos += 1;

    if (pos != cycle_start) {
      update_rec_style(m_element_shape, true, true, pos, m_element_number[pos],
                       sf::Color::Red);
      // sf::sleep(sf::seconds(0.1));
      std::swap(item, m_element_number[pos]);
      update_rec_style(m_element_shape, true, true, pos, m_element_number[pos],
                       sf::Color::White);
      writes++;
    }

    while (pos != cycle_start) {
      pos = cycle_start;

      for (int i = cycle_start + 1; i < n; i++)
        if (m_element_number[i] < item)
          pos += 1;

      while (item == m_element_number[pos])
        pos += 1;

      if (item != m_element_number[pos]) {
        update_rec_style(m_element_shape, true, true, pos,
                         m_element_number[pos], sf::Color::Red);
        // sf::sleep(sf::seconds(0.1));
        std::swap(item, m_element_number[pos]);
        update_rec_style(m_element_shape, true, true, pos,
                         m_element_number[pos], sf::Color::White, true);
        writes++;
      }
    }
  }
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}

void Visualization::weak_heap_sort() {
  int n = m_element_number.size();
  if (n <= 1)
    return;

  std::vector<bool> r(n, false);
  for (int i = n - 1; i > 0; --i) {
    int j = i;
    while ((j & 1) == r[j >> 1])
      j >>= 1;
    int parent = j >> 1;
    weak_heap_merge(r, parent, i);
  }

  for (int i = n - 1; i >= 2; --i) {
    update_rec_style(m_element_shape, false, true, 0, m_element_number[0],
                     sf::Color::Red);
    update_rec_style(m_element_shape, false, true, i, m_element_number[i],
                     sf::Color::Red);
    std::swap(m_element_number[0], m_element_number[i]);
    update_rec_style(m_element_shape, true, true, 0, m_element_number[0],
                     sf::Color::White);
    update_rec_style(m_element_shape, true, true, i, m_element_number[i],
                     sf::Color::White, true);
    int x = 1;
    int y;
    while ((y = 2 * x + (r[x] ? 1 : 0)) < i)
      x = y;
    while (x > 0) {
      weak_heap_merge(r, 0, x);
      x >>= 1;
    }
  }
  update_rec_style(m_element_shape, false, true, 0, m_element_number[0],
                   sf::Color::Red);
  update_rec_style(m_element_shape, false, true, 1, m_element_number[1],
                   sf::Color::Red);
  std::swap(m_element_number[0], m_element_number[1]);
  update_rec_style(m_element_shape, true, true, 0, m_element_number[0],
                   sf::Color::White);
  update_rec_style(m_element_shape, true, true, 1, m_element_number[1],
                   sf::Color::White, true);
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}

void Visualization::weak_heap_merge(std::vector<bool>& r, int parent,
                                    int child) {
  if (m_element_number[parent] < m_element_number[child]) {
    r[child].flip();
    update_rec_style(m_element_shape, false, true, parent,
                     m_element_number[parent], sf::Color::Red);
    update_rec_style(m_element_shape, false, true, child,
                     m_element_number[child], sf::Color::Red);
    std::swap(m_element_number[parent], m_element_number[child]);
    update_rec_style(m_element_shape, true, true, parent,
                     m_element_number[parent], sf::Color::White);
    update_rec_style(m_element_shape, true, true, child,
                     m_element_number[child], sf::Color::White);
  }
}
