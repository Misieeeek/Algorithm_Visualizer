#include <gtest/gtest.h>
#include "sorting_class.h"
#include "visualization.h"

class Visualization_Test : public ::testing::Test {
 protected:
  Visualization visualization;
  Sorting_Class sort_class;
};

//============================INSERTION SORT=======================================
TEST_F(Visualization_Test, insertion_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, insertion_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}
//============================RECURSIVE INSERTION SORT=======================================
TEST_F(Visualization_Test, insertion_sort_recur_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.recur_insertion_sort(test_values.size());
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_recur_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.recur_insertion_sort(test_values.size());
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, insertion_sort_recur_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.recur_insertion_sort(test_values.size());
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_recur_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.recur_insertion_sort(test_values.size());
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_recur_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.recur_insertion_sort(test_values.size());
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_recur_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.recur_insertion_sort(test_values.size());
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_recur_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.recur_insertion_sort(test_values.size());
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================BINARY INSERTION SORT=======================================
TEST_F(Visualization_Test, insertion_sort_binary_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.binary_insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_binary_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.binary_insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, insertion_sort_binary_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.binary_insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_binary_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.binary_insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_binary_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.binary_insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_binary_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.binary_insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, insertion_sort_binary_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.binary_insertion_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | SHELL GAPS =======================================
TEST_F(Visualization_Test, shell_sort_shell_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_shell_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_shell_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_shell_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_shell_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_shell_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_shell_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | F&L GAPS =======================================
TEST_F(Visualization_Test, shell_sort_fl_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  sort_class.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  sort_class.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  sort_class.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  sort_class.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  sort_class.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  sort_class.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  sort_class.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}
