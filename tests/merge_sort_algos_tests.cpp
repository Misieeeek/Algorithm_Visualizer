#include <gtest/gtest.h>
#include "visualization.h"
#include "visualization_options.h"

class Visualization_Test : public ::testing::Test {
 protected:
  Visualization visualization;
  Visualization_Options viz_opt;
};

//============================MERGE SORT=======================================
TEST_F(Visualization_Test, merge_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, merge_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, merge_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, merge_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, merge_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, merge_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, merge_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================CASCADE MERGE SORT=======================================
TEST_F(Visualization_Test, cascade_merge_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.cascade_merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, cascade_merge_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.cascade_merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, cascade_merge_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.cascade_merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, cascade_merge_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.cascade_merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, cascade_merge_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.cascade_merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, cascade_merge_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.cascade_merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, cascade_merge_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.cascade_merge_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}
