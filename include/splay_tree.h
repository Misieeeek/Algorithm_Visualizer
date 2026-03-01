#include "visualization.h"

class Splay_Tree {
 private:
  friend class Visualization;
  struct Node {
    int m_key;
    int m_index;
    int m_count{1};
    int m_size{1};
    int m_visual_index{-1};
    std::unique_ptr<Node> m_left{nullptr};
    std::unique_ptr<Node> m_right{nullptr};
    Node(int val, int ind) : m_key(val), m_index(ind) {}
  };
  int m_root_index{0};
  std::vector<int> m_help_vec{};
  std::unique_ptr<Node> m_root{nullptr};
  std::unique_ptr<Node> right_rotate(std::unique_ptr<Node> x);
  std::unique_ptr<Node> left_rotate(std::unique_ptr<Node> x);
  std::unique_ptr<Node> splay(std::unique_ptr<Node> root, int key);
  int inorder_traversal_with_position(Node* node, int pos,
                                      std::vector<std::pair<int, int>>& result);

 public:
  void insert(int key, int index);
  void splay_sort(std::span<int> data);
  void get_sorted_elements_with_visual_index(
      Node* node, int& current_index, std::vector<std::pair<int, int>>& result);
  void update_all_visual_indices();
  void update_visual_indices(Node* node, int& current_index);
  std::vector<std::pair<int, int>> get_sorted_elements_with_visual_index();
};
