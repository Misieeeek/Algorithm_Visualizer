#include "visualization.h"

class Tree {
 public:
  struct Node {
    int m_key;
    int m_visual_index{0};
    std::unique_ptr<Node> m_left{nullptr};
    std::unique_ptr<Node> m_right{nullptr};

    explicit Node(int key) : m_key(key) {}
  };

  std::unique_ptr<Node> m_root{nullptr};

  void update_visual_indices(Node* node, int& current_index);
  void update_all_visual_indices();
  void store_sorted(Node* root, std::vector<int>& arr, int& i);
  std::unique_ptr<Node> insert(std::unique_ptr<Node>& node, int key);
  std::vector<std::pair<int, int>> get_sorted_elements_with_visual_index();
  void get_sorted_elements_with_visual_index(
      Node* node, int& current_index, std::vector<std::pair<int, int>>& result);
};
