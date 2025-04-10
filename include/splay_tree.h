#include "visualization.h"

class Splay_Tree {
 private:
  struct Node {
    int m_key;
    int m_count;
    std::unique_ptr<Node> m_left;
    std::unique_ptr<Node> m_right;
    Node(int val) : m_key(val), m_count(1), m_left(nullptr), m_right(nullptr) {}
  };
  int m_root_index;
  std::vector<int> m_help_vec;
  std::unique_ptr<Node> m_root;
  std::unique_ptr<Node> right_rotate(std::unique_ptr<Node> x, int index);
  std::unique_ptr<Node> left_rotate(std::unique_ptr<Node> x, int index);
  std::unique_ptr<Node> splay(std::unique_ptr<Node> root, int key, int index);
  void inorder_traversal(Node* node, std::vector<int>& result);

 public:
  Splay_Tree() : m_root(nullptr), m_help_vec({}), m_root_index(0) {}
  ~Splay_Tree() {};
  void insert(int key, int index);
  void splay_sort(std::span<int> data);
  std::vector<int> get_sorted_elements();
};
