
#include <gtest/gtest.h>
#include "visualization.h"
#include "visualization_options.h"

class Visualization_Test : public ::testing::Test {
 protected:
  Visualization visualization;
  Visualization_Options viz_opt;
};

//============================SELECTION SORT=======================================
TEST_F(Visualization_Test, selection_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.selection_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, selection_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.selection_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, selection_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.selection_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, selection_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.selection_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, selection_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.selection_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, selection_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.selection_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, selection_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.selection_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================HEAPSORT=======================================
TEST_F(Visualization_Test, heap_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.heap_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, heap_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.heap_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, heap_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.heap_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, heap_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.heap_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, heap_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.heap_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, heap_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.heap_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, heap_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.heap_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================SMOOTH SORT=======================================
TEST_F(Visualization_Test, smooth_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.smooth_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, smooth_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.smooth_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, smooth_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.smooth_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, smooth_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.smooth_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, smooth_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.smooth_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, smooth_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.smooth_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, smooth_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.smooth_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================CARTESIAN TREE SORT=======================================
TEST_F(Visualization_Test, cartesian_tree_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.cartesian_tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, cartesian_tree_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.cartesian_tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, cartesian_tree_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.cartesian_tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, cartesian_tree_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.cartesian_tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, cartesian_tree_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.cartesian_tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, cartesian_tree_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.cartesian_tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, cartesian_tree_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.cartesian_tree_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

//============================TOURNAMENT SORT=======================================
TEST_F(Visualization_Test, tournament_sort_sorts_corretcly) {
  std::vector<int> test_values = {5, 3, 8, 6, 2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.tournament_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, tournament_sort_handles_empty_array) {
  std::vector<int> test_values{};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.tournament_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_TRUE(visualization.test_get_elements().empty());
}

TEST_F(Visualization_Test, tournament_sort_handles_single_element) {
  std::vector<int> test_values = {42};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.tournament_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, tournament_sort_handles_already_sorted_array) {
  std::vector<int> test_values = {1, 2, 3, 4, 5};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.tournament_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, tournament_sort_handles_reverse_sorted_array) {
  std::vector<int> test_values = {5, 4, 3, 2, 1};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.tournament_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, tournament_sort_handles_negative_values) {
  std::vector<int> test_values = {-5, -3, -8, -6, -2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.tournament_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}

TEST_F(Visualization_Test, tournament_sort_handles_mixed_values) {
  std::vector<int> test_values = {-5, -3, 8, -6, 2};
  visualization.test_set_elements(test_values);
  visualization.test_set_aux_elements(test_values.size(), 1);
  visualization.tournament_sort();
  std::sort(test_values.begin(), test_values.end());
  EXPECT_EQ(visualization.test_get_elements(), test_values);
}
