#include <iostream>
#include <string>
#include <vector>

using Number = long long;

const Number N = 1e9 + 7;

struct Node {
  Number x;
  Number y;
  Number amount;
  Number product_subtreap;
  Node* left;
  Node* right;

  Node(Number x, Number y): x(x), y(y), amount(1), product_subtreap(x % N), left(nullptr), right(nullptr) {}

  Node *get_child(Number value) {
    if (x < value) {
      return right;
    }
    return left;
  }
};

Number get_product_node(Node* node) {
  Number product = 1;
  if (!node) {
    return product;
  }
  for (size_t i = 0; i < node->amount; ++i) {
    product = (product * (node->x % N)) % N;
  }
  return product % N;
}

Number get_product_subtreap(Node* node) {
  if (!node) {
    return 1;
  }
  return node->product_subtreap % N;
}

Number update_product_subtreap(Node* node) {
  if (!node) {
    return 1;
  }
  return (((get_product_subtreap(node->left) * get_product_subtreap(node->right)) % N) * get_product_node(node)) % N;
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
    left_tree->product_subtreap = update_product_subtreap(left_tree);
    return left_tree;
  }
  right_tree->left = merge(left_tree, right_tree->left);
  right_tree->product_subtreap = update_product_subtreap(right_tree);
  return right_tree;
}

std::pair<Node*, Node*> split(Node* root, Number x) {
  if (!root) {
    return std::pair{nullptr, nullptr};
  }
  if (root->x < x) {
    auto [left_tree, right_tree] = split(root->right, x);
    root->right = left_tree;
    root->product_subtreap = update_product_subtreap(root);
    return std::pair(root, right_tree);
  }
  auto [left_tree, right_tree] = split(root->left, x);
  root->left = right_tree;
  root->product_subtreap = update_product_subtreap(root);
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

  Node *find(long long x) {
    Node *now = root;
    while (now && now->x != x) {
      now = now->get_child(x);
    }
    if (!now || now->x != x) {
      return nullptr;
    }
    return now;
  }

  void update(Node* now, const Node* stop) {
    if (!now) {
      return;
    }
    if (now->x == stop->x) {
      now->product_subtreap = update_product_subtreap(now);
      return;
    }
    if (now->x > stop->x) {
      update(now->left, stop);
    } else {
      update(now->right, stop);
    }
    now->product_subtreap = update_product_subtreap(now);
  }

  void insert(int x, int y) {
    if (!root) {
      root = new Node(x, y);
      return;
    }
    Node* found = find(x);
    if (found) {
      ++found->amount;
      update(root, found);
      return;
    }
    Node* new_node = new Node(x, y);
    auto [left_tree, right_tree] = split(root, x);
    root = merge(left_tree, new_node);
    root = merge(root, right_tree);
  }

  void erase(int x) {
    Node* found = find(x);
    if (!found) {
      return;
    }
    if (found->amount > 1) {
      --found->amount;
      update(root, found);
      return;
    }
    auto [left_tree, right_tree] = split(root, x);
    auto [second_left_tree, second_right_tree] = split(right_tree, x + 1);
    delete second_left_tree;
    root = merge(left_tree, second_right_tree);
  }

  Number get_product(Number L, Number R) {
    if (!root) {
      return 1;
    }
    auto [left_tree, right_tree] = split(root, L);
    auto [second_left_tree, second_right_tree] = split(right_tree, R + 1);
    Number result = get_product_subtreap(second_left_tree);
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
    int x;
    if (command == "INSERT") {
      std::cin >> x;
      treap.insert(x, std::rand());
    } else if (command == "ERASE") {
      std::cin >> x;
      treap.erase(x);
    } else if (command == "PRODUCT") {
      Number L, R;
      std::cin >> L >> R;
      result.push_back(treap.get_product(L, R));
    }
  }

  for (Number res : result) {
    std::cout << res << "\n";
  }
}