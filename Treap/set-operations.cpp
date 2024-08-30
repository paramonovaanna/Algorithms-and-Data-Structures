#include <iostream>
#include <string>
#include <vector>

struct Node {
  int x;
  int y;
  int distance = 0;
  Node *left;
  Node *right;
  Node(int x, int y) : x(x), y(y), distance(-1), left(nullptr), right(nullptr) {}

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
  if (root->x <= x) {
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

  int find(int x) {
    int distance = -1;
    Node *now = root_ptr;
    while (now && now->x != x) {
      now = now->get_child(x);
      ++distance;
    }
    if (!now || now->x != x) {
        return -1;
    }
    ++distance;
    return distance;
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

  void erase(int x) {
    if (find(x) == -1) {
        return;
    }
    auto [left_tree, right_tree] = split(root_ptr, x - 1);
    auto [second_left_tree, second_right_tree] = split(right_tree, x);
    delete second_left_tree;
    root_ptr = merge(left_tree, second_right_tree);
  }

  bool is_leaf(Node *node) { return !node->left && !node->right; }

  int get_distance(int x) {
    return find(x);
  }

private:
  Node *root_ptr;
};

int main() {
  Treap treap;
  std::vector<int> result;
  int n;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    std::string command;
    std::cin >> command;
    int x;
    std::cin >> x;
    if (command == "CONTAINS") {
        result.push_back(treap.get_distance(x));
    } else if (command == "ERASE") {
        treap.erase(x);
    } else if (command == "INSERT") {
        int y;
        std::cin >> y;
        treap.insert(x, y);
        int a = 1;
    }
  }
  for (int res : result) {
    std::cout << res << "\n";
  }
}