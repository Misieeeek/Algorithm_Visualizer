#include <gtest/gtest.h>
#include "visualization.h"

class Visualization_Test : public ::testing::Test {
 protected:
  Visualization visualization;
};

TEST_F(Visualization_Test, sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}
