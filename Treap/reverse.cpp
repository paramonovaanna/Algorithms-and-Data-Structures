#include <iostream>
#include <vector>

using Number = int;

const int INF = 1e9;

struct Node {
  Number y;
  Number value;
  Number subtreap_size;
  Number subtreap_minval;
  bool reversed;
  Node* left;
  Node* right;

  Node(Number y, Number value): y(y), value(value), subtreap_size(1), subtreap_minval(value), reversed(0), left(nullptr), right(nullptr) {}
};

void push(Node* node) {
  if (!node) {
    return;
  }
  if (node->reversed) {
    std::swap(node->left, node->right);
    if (node->left) {
      node->left->reversed ^= 1;
    }
    if (node->right) {
      node->right->reversed ^= 1;
    }
    node->reversed = 0;
  }
}

Number get_subtreap_minval(Node* node) {
  if (!node) {
    return INF;
  }
  return node->subtreap_minval;
}

Number get_subtreap_size(Node* node) {
  if (!node) {
    return 0;
  }
  return node->subtreap_size;
}

void update_subtreap(Node* node) {
  if (!node) {
    return;
  }
  node->subtreap_size = get_subtreap_size(node->left) + get_subtreap_size(node->right) + 1;

  node->subtreap_minval = std::min(get_subtreap_minval(node->left), get_subtreap_minval(node->right));
  node->subtreap_minval = std::min(get_subtreap_minval(node), node->value);
}

Node* merge(Node* left_tree, Node* right_tree) {
  if (!left_tree) {
    return right_tree;
  }
  if (!right_tree) {
    return left_tree;
  }
  push(left_tree);
  push(right_tree);
  if (left_tree->y > right_tree->y) {
    left_tree->right = merge(left_tree->right, right_tree);
    update_subtreap(left_tree);
    return left_tree;
  }
  right_tree->left = merge(left_tree, right_tree->left);
  update_subtreap(right_tree);
  return right_tree;
}

std::pair<Node*, Node*> split(Node* root, Number index) {
  if (!root) {
    return std::pair{nullptr, nullptr};
  }
  push(root);
  if (get_subtreap_size(root->left) < index) {
    auto [left_tree, right_tree] = split(root->right, index - get_subtreap_size(root->left) - 1);
    root->right = left_tree;
    update_subtreap(root);
    return std::pair(root, right_tree);
  }
  auto [left_tree, right_tree] = split(root->left, index);
  root->left = right_tree;
  update_subtreap(root);
  return std::pair(left_tree, root);
}

class Treap {
public:
  Treap() { root = nullptr; };

  ~Treap() { delete_treap(root); }

  void delete_treap(Node *now) {
    if (now) {
      delete_treap(now->left);
      delete_treap(now->right);
      delete now;
    }
  }

  void PushBack(Number y, Number value) {
    Node* new_node = new Node(y, value);
    root = merge(root, new_node);
  }

  Number get_minval(Number L, Number R) {
    auto [left_tree, right_tree] = split(root, L);
    auto [second_left_tree, second_right_tree] = split(right_tree, R - L + 1);
    Number result = get_subtreap_minval(second_left_tree);
    root = merge(left_tree, merge(second_left_tree, second_right_tree));
    return result;
  }

  void reverse(Number L, Number R) {
    auto [left_tree, right_tree] = split(root, L);
    auto [second_left_tree, second_right_tree] = split(right_tree, R - L + 1);
    if (second_left_tree) {
      second_left_tree->reversed ^= 1;
    }
    root = merge(left_tree, merge(second_left_tree, second_right_tree));
  }

private:
  Node* root;
};


int main() {
  Treap treap;
  Number n, m;
  std::cin >> n >> m;
  for (size_t i = 0; i < n; ++i) {
    Number value;
    std::cin >> value;
    treap.PushBack(std::rand(), value);
  }

  std::vector<Number> result;
  for (size_t i = 0; i < m; ++i) {
    Number command, L, R;
    std::cin >> command >> L >> R;
    if (command == 1) {
      treap.reverse(L - 1, R - 1);
    }
    if (command == 2) {
      result.push_back(treap.get_minval(L - 1, R - 1));
    }
  }
  for (Number res : result) {
    std::cout << res << "\n";
  }
}