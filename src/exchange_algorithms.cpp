#include "visualization.h"
int Visualization::help_partition(std::vector<int>& arr, int l, int h) {
  int x = arr[h];
  int i = (l - 1);

  for (int j = l; j <= h - 1; j++) {
    if (arr[j] <= x) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[h]);
  return (i + 1);
}

std::vector<int> Visualization::help_sort(std::vector<int>& arr) {
  if (arr.size() <= 1)
    return arr;
  int h = arr.size() - 1;
  int l = 0;
  std::vector<int> stack(h - l + 1);
  int top = -1;

  stack[++top] = l;
  stack[++top] = h;

  while (top >= 0) {
    h = stack[top--];
    l = stack[top--];

    int p = help_partition(arr, l, h);

    if (p - 1 > l) {
      stack[++top] = l;
      stack[++top] = p - 1;
    }

    if (p + 1 < h) {
      stack[++top] = p + 1;
      stack[++top] = h;
    }
  }
  return arr;
}
