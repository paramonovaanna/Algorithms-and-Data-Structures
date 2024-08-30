#include <iostream>
#include <string>
#include <vector>

struct Node {
  int x;
  int y;
  int amount;
  int size_subtreap;
  Node *left;
  Node *right;
  Node(int x, int y)
      : x(x), y(y), amount(1), size_subtreap(1), left(nullptr), right(nullptr) {
  }

  Node *get_child(int value) {
    if (x < value) {
      return right;
    }
    return left;
  }
};

int get_size_subtreap(Node* node) {
    if (!node) {
        return 0;
    }
    return node->size_subtreap;
}

Node *merge(Node *left_tree, Node *right_tree) {
  if (!left_tree) {
    return right_tree;
  }
  if (!right_tree) {
    return left_tree;
  }
  if (left_tree->y > right_tree->y) {
    left_tree->size_subtreap += get_size_subtreap(right_tree);
    left_tree->right = merge(left_tree->right, right_tree);
    return left_tree;
  }
  right_tree->size_subtreap += get_size_subtreap(left_tree);
  right_tree->left = merge(left_tree, right_tree->left);
  return right_tree;
}

std::pair<Node *, Node *> split(Node *root, int x) {
  if (!root) {
    return std::pair(nullptr, nullptr);
  }
  if (root->x < x) {
    root->size_subtreap -= get_size_subtreap(root->right);
    auto [left_tree, right_tree] = split(root->right, x);
    root->size_subtreap += get_size_subtreap(left_tree);
    root->right = left_tree;
    return std::pair(root, right_tree);
  }
  root->size_subtreap -= get_size_subtreap(root->left);
  auto [left_tree, right_tree] = split(root->left, x);
  root->size_subtreap += get_size_subtreap(right_tree);
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
    if (!now || now->x != x) {
      return nullptr;
    }
    return now;
  }

  void update(int x, int delta) {
    Node *now = root_ptr;
    while (now->x != x) {
      now->size_subtreap += delta;
      if (now->x < x) {
        now = now->right;
      } else {
        now = now->left;
      }
    }
  }

  void insert(int x, int y) {
    Node *found = find(x);
    if (found != nullptr) {
      update(x, 1);
      ++found->amount;
      ++found->size_subtreap;
      return;
    }
    if (root_ptr == nullptr) {
      root_ptr = new Node(x, y);
      return;
    }
    Node *node = new Node(x, y);
    auto [left_tree, right_tree] = split(root_ptr, x);
    root_ptr = merge(left_tree, node);
    root_ptr = merge(root_ptr, right_tree);
  }

  void erase(int x) {
    Node *node = find(x);
    if (node == nullptr) {
      return;
    }
    if (node->amount > 1) {
      update(x, -1);
      --node->amount;
      --node->size_subtreap;
      return;
    }
    auto [left_tree, right_tree] = split(root_ptr, x);
    auto [second_left_tree, second_right_tree] = split(right_tree, x + 1);
    delete second_left_tree;
    root_ptr = merge(left_tree, second_right_tree);
  }

  int get_element(int index) {
    if (!root_ptr || index > root_ptr->size_subtreap) {
        return -1;
    }
    Node* now = root_ptr;
    int right, left = -1;
    while (now) {
        left = get_size_subtreap(now->left);
        right = get_size_subtreap(now->right);
        if (index >= left && index < left + now->amount) {
            return now->x;
        }
        if (index < left) {
            now = now->left;
        } else if (index >= left + now->amount) {
            index -= left + now->amount;
            now = now->right;
        }
    }
    return -1;
  }

  

private:
  Node *root_ptr;
  int k_number;
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
    if (command == "GET") {
      result.push_back(treap.get_element(x));
      int a = 1;
    } else if (command == "ERASE") {
      treap.erase(x);
      int a = 1;
    } else if (command == "INSERT") {
      treap.insert(x, std::rand());
      int a = 1;
    }
  }
  for (int res : result) {
    std::cout << res << "\n";
  }
}