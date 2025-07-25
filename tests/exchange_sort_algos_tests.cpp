#include <gtest/gtest.h>
#include "visualization.h"
#include "visualization_options.h"

class Visualization_Test : public ::testing::Test {
 protected:
  Visualization visualization;
  Visualization_Options viz_opt;
};

//============================HELP SORT=======================================
TEST_F(Visualization_Test, help_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_aux_elements(test_values.size(), 2);
  std::vector<int> result = visualization.help_sort(test_values, 0);
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(result, test_values);
}

TEST_F(Visualization_Test, help_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_aux_elements(test_values.size(), 2);
  std::vector<int> result = visualization.help_sort(test_values, 0);
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, help_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_aux_elements(test_values.size(), 2);
  std::vector<int> result = visualization.help_sort(test_values, 0);
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(result, test_values);
}

TEST_F(Visualization_Test, help_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_aux_elements(test_values.size(), 2);
  std::vector<int> result = visualization.help_sort(test_values, 0);
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(result, test_values);
}

TEST_F(Visualization_Test, help_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_aux_elements(test_values.size(), 2);
  std::vector<int> result = visualization.help_sort(test_values, 0);
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(result, test_values);
}

TEST_F(Visualization_Test, help_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_aux_elements(test_values.size(), 2);
  std::vector<int> result = visualization.help_sort(test_values, 0);
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(result, test_values);
}

TEST_F(Visualization_Test, help_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_aux_elements(test_values.size(), 2);
  std::vector<int> result = visualization.help_sort(test_values, 0);
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(result, test_values);
}
