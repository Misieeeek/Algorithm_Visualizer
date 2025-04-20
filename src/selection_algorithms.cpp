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
    int trail = __builtin_ctz(p & ~1);
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
      int trail = __builtin_ctz(p & ~1);
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
