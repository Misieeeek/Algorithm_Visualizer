#include "visualization.h"

void Visualization::merge_sort() {
  merge_sort(0, m_element_number.size() - 1);
  restart_timer();
  m_buttons_text[1].setString("Start");
  m_stop_visualizing.store(true);
  m_visualizaing = false;
}

void Visualization::merge_sort(int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    merge_sort(l, m);
    merge_sort(m + 1, r);
    merge(l, m, r);
  }
}

void Visualization::merge(int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;
  std::vector<int> L(n1);
  std::vector<int> M(n2);
  for (int i = 0; i < n1; i++)
    L[i] = m_element_number[p + i];

  for (int j = 0; j < n2; j++)
    M[j] = m_element_number[q + 1 + j];

  int i = 0, j = 0, k = p;

  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      update_rec_style(m_element_shape, false, true, k, m_element_number[k],
                       sf::Color::Red);
      m_element_number[k] = L[i];
      update_rec_style(m_element_shape, true, true, k, m_element_number[k],
                       sf::Color::White);
      i++;
    } else {
      update_rec_style(m_element_shape, false, true, k, m_element_number[k],
                       sf::Color::Red);
      m_element_number[k] = M[j];
      update_rec_style(m_element_shape, true, true, k, m_element_number[k],
                       sf::Color::White);
      j++;
    }
    k++;
    update_rec_style(m_element_shape, false, false, k, m_element_number[k],
                     sf::Color::White, true);
  }

  while (i < n1) {
    update_rec_style(m_element_shape, false, true, k, m_element_number[k],
                     sf::Color::Red);
    m_element_number[k] = L[i];
    update_rec_style(m_element_shape, true, true, k, m_element_number[k],
                     sf::Color::White, true);
    i++;
    k++;
  }

  while (j < n2) {
    update_rec_style(m_element_shape, false, true, k, m_element_number[k],
                     sf::Color::Red);
    m_element_number[k] = M[j];
    update_rec_style(m_element_shape, true, true, k, m_element_number[k],
                     sf::Color::White, true);
    j++;
    k++;
  }
}

std::vector<int> Visualization::merge_two(const std::vector<int>& A,
                                          const std::vector<int>& B) {
  std::vector<int> R;
  R.reserve(A.size() + B.size());
  size_t i = 0, j = 0;
  while (i < A.size() && j < B.size()) {
    if (A[i] < B[j]) {
      R.push_back(A[i++]);
    } else {
      R.push_back(B[j++]);
    }
  }
  while (i < A.size())
    R.push_back(A[i++]);
  while (j < B.size())
    R.push_back(B[j++]);
  return R;
}

void Visualization::cascade_merge_sort() {
  if (m_element_number.size() <= 1)
    return;
  size_t block_size = 2;
  std::vector<std::vector<int>> blocks;
  blocks.reserve((m_element_number.size() + block_size - 1) / block_size);
  for (size_t start = 0; start < m_element_number.size(); start += block_size) {
    size_t end = std::min(start + block_size, m_element_number.size());
    std::vector<int> block(m_element_number.begin() + start,
                           m_element_number.begin() + end);
    std::sort(block.begin(), block.end());
    blocks.push_back(std::move(block));
  }

  std::vector<int> result = std::move(blocks[0]);
  for (size_t i = 1; i < blocks.size(); ++i) {
    result = merge_two(result, blocks[i]);
  }
  for (int i = 0; i < m_element_number.size(); i++) {
    m_element_number[i] = result[i];
  }
}
