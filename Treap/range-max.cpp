#include <iostream>
#include <string>
#include <vector>

using Number = int;

struct Node {
  Number x;
  Number y;
  Number value;
  Number subtreap_size;
  Number subtreap_max_val;
  Node* left;
  Node* right;

  Node(Number x, Number y, Number value): x(x), y(y), value(value), subtreap_size(1), subtreap_max_val(value), left(nullptr), right(nullptr) {}
};

Number get_subtreap_maxval(Node* node) {
  if (!node) {
    return -1;
  }
  return node->subtreap_max_val;
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

  node->subtreap_max_val = std::max(get_subtreap_maxval(node->left), get_subtreap_maxval(node->right));
  node->subtreap_max_val = std::max(node->subtreap_max_val, node->value);
}

Node* merge(Node* left_tree, Node* right_tree) {
  if (!left_tree) {
    return right_tree;
  }
  if (!right_tree) {
    return left_tree;
  }
  if (left_tree->y > right_tree->y) {
    left_tree->right = merge(left_tree->right, right_tree);
    update_subtreap(left_tree);
    return left_tree;
  }
  right_tree->left = merge(left_tree, right_tree->left);
  update_subtreap(right_tree);
  return right_tree;
}

std::pair<Node*, Node*> split(Node* root, Number x) {
  if (!root) {
    return std::pair{nullptr, nullptr};
  }
  if (root->x < x) {
    auto [left_tree, right_tree] = split(root->right, x);
    root->right = left_tree;
    update_subtreap(root);
    return std::pair(root, right_tree);
  }
  auto [left_tree, right_tree] = split(root->left, x);
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

  void insert(Number x, Number y, Number value) {
    if (!root) {
      root = new Node(x, y, value);
      return;
    }
    Node* new_node = new Node(x, y, value);
    auto [left_tree, right_tree] = split(root, x);
    root = merge(left_tree, new_node);
    root = merge(root, right_tree);
  }

  void erase(int x) {
    auto [left_tree, right_tree] = split(root, x);
    auto [second_left_tree, second_right_tree] = split(right_tree, x + 1);
    if (second_left_tree) {
      delete second_left_tree;
    }
    root = merge(left_tree, second_right_tree);
  }

  Number get_maxval(Number L, Number R) {
    auto [left_tree, right_tree] = split(root, L);
    auto [second_left_tree, second_right_tree] = split(right_tree, R + 1);
    Number result = get_subtreap_maxval(second_left_tree);
    root = merge(left_tree, merge(second_left_tree, second_right_tree));
    return result;
  }

private:
  Node* root;
};


int main() {
  Treap treap;
  Number n;
  std::cin >> n;

  std::vector<Number> result;
  for (size_t i = 0; i < n; ++i) {
    std::string command;
    std::cin >> command;
    Number x;
    if (command == "INSERT") {
      Number value;
      std::cin >> x >> value;
      treap.insert(x, std::rand(), value);
    } else if (command == "ERASE") {
      std::cin >> x;
      treap.erase(x);
    } else if (command == "MAXVAL") {
      Number L, R;
      std::cin >> L >> R;
      result.push_back(treap.get_maxval(L, R));
    }
  }
  for (Number res : result) {
    std::cout << res << "\n";
  }
}