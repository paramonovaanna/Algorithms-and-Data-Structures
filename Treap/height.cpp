#include <iostream>

struct Node {
  int x;
  int y;
  int subtreap_height;
  Node *left;
  Node *right;
  Node(int x, int y) : x(x), y(y), subtreap_height(0), left(nullptr), right(nullptr) {}

  Node *get_child(int value) {
    if (x < value) {
      return right;
    }
    return left;
  }
};

Node *merge(Node *left_tree, Node *right_tree) {
  if (!left_tree) {
    return right_tree;
  }
  if (!right_tree) {
    return left_tree;
  }
  if (left_tree->y > right_tree->y) {
    left_tree->right = merge(left_tree->right, right_tree);
    return left_tree;
  }
  right_tree->left = merge(left_tree, right_tree->left);
  int a = 1;
  return right_tree;
}

std::pair<Node *, Node *> split(Node *root, int x) {
  if (!root) {
    return std::pair(nullptr, nullptr);
  }
  if (root->x < x) {
    auto [left_tree, right_tree] = split(root->right, x);
    root->right = left_tree;
    return std::pair(root, right_tree);
  }
  auto [left_tree, right_tree] = split(root->left, x);
  root->left = right_tree;
  return std::pair(left_tree, root);
}

class Treap {
public:
  Treap() { root_ptr = nullptr; };

  ~Treap() { delete_treap(root_ptr); }

  void delete_treap(Node *now) {
    if (now) {
      delete_treap(now->left);
      delete_treap(now->right);
      delete now;
    }
  }

  Node *find(int x) {
    Node *now = root_ptr;
    while (now && now->x != x) {
      now = now->get_child(x);
    }
    return now;
  }

  void insert(int x, int y) {
    if (root_ptr == nullptr) {
      root_ptr = new Node(x, y);
      return;
    }
    Node *node = new Node(x, y);
    auto [left_tree, right_tree] = split(root_ptr, x);
    root_ptr = merge(left_tree, node);
    root_ptr = merge(root_ptr, right_tree);
    int a  = 1;
  }

  bool is_leaf(Node *node) { return !node->left && !node->right; }

  int calculate_subtreaps_height(Node* node) {
    if (!node) {
      return 0;
    }
    if (is_leaf(node)) {
      ++node->subtreap_height;
      return node->subtreap_height;
    }
    node->subtreap_height = std::max(calculate_subtreaps_height(node->right),
                                    calculate_subtreaps_height(node->left)) +
                           1;
    return node->subtreap_height;
  }

  int get_height() {
    calculate_subtreaps_height(root_ptr);
    return root_ptr->subtreap_height - 1;
  }

private:
  Node *root_ptr;
};

int main() {
  Treap treap;
  int n;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    treap.insert(x, y);
  }
  std::cout << treap.get_height();
}