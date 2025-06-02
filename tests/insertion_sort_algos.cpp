#include <gtest/gtest.h>
#include "visualization.h"
#include "visualization_options.h"

class Visualization_Test : public ::testing::Test {
 protected:
  Visualization visualization;
  Visualization_Options viz_opt;
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
  viz_opt.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_fl_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(1);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | HIBBARD GAPS =======================================
TEST_F(Visualization_Test, shell_sort_hibbard_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(2);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_hibbard_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(2);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_hibbard_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(2);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test,
       shell_sort_hibbard_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(2);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test,
       shell_sort_hibbard_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(2);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_hibbard_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(2);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_hibbard_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(2);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | PAPERNOV & STASEVICH GAPS =======================================
TEST_F(Visualization_Test, shell_sort_ps_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(3);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_ps_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(3);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_ps_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(3);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_ps_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(3);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_ps_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(3);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_ps_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(3);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_ps_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(3);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT |  PRATT GAPS =======================================
TEST_F(Visualization_Test, shell_sort_pratt_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(4);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_pratt_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(4);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_pratt_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(4);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_pratt_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(4);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_pratt_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(4);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_pratt_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(4);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_pratt_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(4);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | KNUTH GAPS =======================================
TEST_F(Visualization_Test, shell_sort_knuth_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(5);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_knuth_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(5);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_knuth_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(5);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_knuth_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(5);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_knuth_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(5);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_knuth_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(5);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_knuth_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(5);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | INCERPI & SADGEWICK GAPS =======================================
TEST_F(Visualization_Test, shell_sort_is_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(6);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_is_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(6);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_is_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(6);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_is_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(6);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_is_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(6);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_is_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(6);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_is_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(6);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | SEDGEWICK (1) GAPS =======================================
TEST_F(Visualization_Test, shell_sort_sedgewick_1_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(7);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_sedgewick_1_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(7);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_sedgewick_1_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(7);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test,
       shell_sort_sedgewick_1_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(7);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test,
       shell_sort_sedgewick_1_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(7);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test,
       shell_sort_sedgewick_1_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(7);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_sedgewick_1_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(7);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | SEDGEWICK (2) GAPS =======================================
TEST_F(Visualization_Test, shell_sort_sedgewick_2_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(8);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_sedgewick_2_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(8);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_sedgewick_2_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(8);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test,
       shell_sort_sedgewick_2_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(8);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test,
       shell_sort_sedgewick_2_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(8);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test,
       shell_sort_sedgewick_2_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(8);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_sedgewick_2_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(8);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | GONNET & BAEZA-YATES GAPS =======================================
TEST_F(Visualization_Test, shell_sort_gby_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(9);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_gby_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(9);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_gby_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(9);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_gby_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(9);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_gby_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(9);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_gby_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(9);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_gby_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(9);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | TOKUDA GAPS =======================================
TEST_F(Visualization_Test, shell_sort_tokuda_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(10);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_tokuda_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(10);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_tokuda_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(10);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test,
       shell_sort_tokuda_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(10);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test,
       shell_sort_tokuda_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(10);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_tokuda_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(10);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_tokuda_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(10);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | CIURA GAPS =======================================
TEST_F(Visualization_Test, shell_sort_ciura_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(11);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_ciura_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(11);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_ciura_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(11);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_ciura_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(11);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_ciura_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(11);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_ciura_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(11);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_ciura_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(11);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | LEE GAPS =======================================
TEST_F(Visualization_Test, shell_sort_lee_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(13);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_lee_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(13);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_lee_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(13);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_lee_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(13);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_lee_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(13);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_lee_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(13);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_lee_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(13);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SHELL SORT | SEJ GAPS =======================================
TEST_F(Visualization_Test, shell_sort_sej_gaps_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(12);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_sej_gaps_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(12);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, shell_sort_sej_gaps_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(12);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_sej_gaps_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(12);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_sej_gaps_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(12);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_sej_gaps_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(12);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, shell_sort_sej_gaps_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  viz_opt.set_additional_option_index(12);
  visualization.shell_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SPLAY SORT=======================================
TEST_F(Visualization_Test, splay_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.splay_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, splay_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.splay_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, splay_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.splay_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, splay_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.splay_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, splay_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.splay_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, splay_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.splay_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, splay_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.splay_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================TREE SORT=======================================
TEST_F(Visualization_Test, tree_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, tree_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, tree_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, tree_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, tree_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);

  visualization.tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, tree_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, tree_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================LIBRARY SORT=======================================
TEST_F(Visualization_Test, library_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 2);
  visualization.library_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, library_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 2);
  visualization.library_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, library_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 2);
  visualization.library_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, library_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 2);
  visualization.library_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, library_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 2);
  visualization.library_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, library_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 2);
  visualization.library_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, library_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 2);
  visualization.library_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}
