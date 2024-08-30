#include <iostream>
#include <string>
#include <vector>

using Number = int;

struct Node {
  Number y;
  Number value;
  Number subtreap_size;
  Node *left;
  Node *right;

  Node(Number y, Number value)
      : y(y), value(value), subtreap_size(1), left(nullptr), right(nullptr) {}
};

Number get_subtreap_size(Node *node) {
  if (!node) {
    return 0;
  }
  return node->subtreap_size;
}

void update_subtreap_size(Node *node) {
  if (!node) {
    return;
  }
  node->subtreap_size =
      get_subtreap_size(node->left) + get_subtreap_size(node->right) + 1;
}

Node *merge(Node *left_tree, Node *right_tree) {
  if (!left_tree) {
    return right_tree;
  }
  if (!right_tree) {
    return left_tree;
  }
  if (left_tree->y > right_tree->y) {
    left_tree->right = merge(left_tree->right, right_tree);
    update_subtreap_size(left_tree);
    return left_tree;
  }
  right_tree->left = merge(left_tree, right_tree->left);
  update_subtreap_size(right_tree);
  return right_tree;
}

std::pair<Node *, Node *> split(Node *root, Number x) {
  if (!root) {
    return std::pair{nullptr, nullptr};
  }
  if (get_subtreap_size(root->left) + 1 < x) {
    auto [left_tree, right_tree] =
        split(root->right, x - get_subtreap_size(root->left) - 1);
    root->right = left_tree;
    update_subtreap_size(root);
    return std::pair(root, right_tree);
  }
  auto [left_tree, right_tree] = split(root->left, x);
  root->left = right_tree;
  update_subtreap_size(root);
  return std::pair(left_tree, root);
}

class Treap {
public:
  Treap() { root = nullptr; }

  ~Treap() { delete_treap(root); }

  void delete_treap(Node *now) {
    if (now) {
      delete_treap(now->left);
      delete_treap(now->right);
      delete now;
    }
  }

  Node *ctrlx(int L, int R) {
    auto [left_tree, right_tree] = split(root, L);
    auto [second_left_tree, second_right_tree] = split(right_tree, R - L + 2);
    root = merge(left_tree, second_right_tree);
    return second_left_tree;
  }

  void ctrlv(Node *tree, Number pos) {
    auto [left_tree, right_tree] = split(root, pos);
    root = merge(left_tree, tree);
    root = merge(root, right_tree);
  }

  void move_positions(Number L, Number R) {
    Node *to_move = ctrlx(L, R);
    ctrlv(to_move, 0);
  }

  void set_values(Node* now) {
    if (now->left) {
      set_values(now->left);
    }
    now->value = order;
    ++order;
    if (now->right) {
      set_values(now->right);
    }
  }

  void in_order(Node* now) {
    if (now->left) {
      in_order(now->left);
    }
    std::cout << now->value << " ";
    if (now->right) {
      in_order(now->right);
    }
  }

  Node* get_root() {
    return root;
  }

  private:
    Node *root;
    Number order = 1;
  };

int main() {
    Treap treap;
    Number n, m;
    std::cin >> n >> m;

    for (size_t i = 0; i < n; ++i) {
      Node *node = new Node(std::rand(), i + 1);
      treap.ctrlv(node, i + 1);
    }
    treap.set_values(treap.get_root());

    for (size_t i = 0; i < m; ++i) {
      Number L, R;
      std::cin >> L >> R;
      treap.move_positions(L, R);
    }
    treap.in_order(treap.get_root());
}