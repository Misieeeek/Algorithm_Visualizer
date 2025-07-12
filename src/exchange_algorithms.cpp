#include "SFML/System/Sleep.hpp"
#include "SFML/System/Time.hpp"
#include "visualization.h"
int Visualization::help_partition(std::vector<int>& arr, int low, int high,
                                  int begin_visual_index) {
  int x = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] <= x) {
      i++;
      update_rec_style(m_auxiliary_shape, true, false, begin_visual_index + i,
                       arr[i], sf::Color::White);
      update_rec_style(m_auxiliary_shape, true, false, begin_visual_index + j,
                       arr[j], sf::Color::White);
      std::swap(arr[i], arr[j]);
      update_rec_style(m_auxiliary_shape, true, false, begin_visual_index + i,
                       arr[i], sf::Color::White);
      update_rec_style(m_auxiliary_shape, true, false, begin_visual_index + j,
                       arr[j], sf::Color::White);
    }
  }
  update_rec_style(m_auxiliary_shape, true, false, begin_visual_index + i + 1,
                   arr[i + 1], sf::Color::White);
  update_rec_style(m_auxiliary_shape, true, false, begin_visual_index + high,
                   arr[high], sf::Color::White);
  std::swap(arr[i + 1], arr[high]);
  update_rec_style(m_auxiliary_shape, true, false, begin_visual_index + i + 1,
                   arr[i + 1], sf::Color::White);
  update_rec_style(m_auxiliary_shape, true, false, begin_visual_index + high,
                   arr[high], sf::Color::White);
  return (i + 1);
}

std::vector<int> Visualization::help_sort(std::vector<int>& arr,
                                          int begin_visual_index) {
  if (arr.size() <= 1)
    return arr;
  int high = arr.size() - 1;
  int low = 0;
  std::vector<int> stack(high - low + 1);
  int top = -1;

  stack[++top] = low;
  stack[++top] = high;

  while (top >= 0) {
    high = stack[top--];
    low = stack[top--];

    int p = help_partition(arr, low, high, begin_visual_index);

    if (p - 1 > low) {
      stack[++top] = low;
      stack[++top] = p - 1;
    }

    if (p + 1 < high) {
      stack[++top] = p + 1;
      stack[++top] = high;
    }
  }
  return arr;
}
