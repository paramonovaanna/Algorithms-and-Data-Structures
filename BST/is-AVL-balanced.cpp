#include <iostream>

struct BstNode {
  int key;
  BstNode *left;
  BstNode *right;
  int subtree_height;
  BstNode(int key) : key(key), left(nullptr), right(nullptr), subtree_height(0) {}

  BstNode *get_child(int value) {
    if (key < value) {
      return right;
    }
    return left;
  }
};

class BST {
public:
  BST() { root_ptr = nullptr; };

  ~BST() { delete_bst(root_ptr); }

  void delete_bst(BstNode *now) {
    if (now) {
      delete_bst(now->left);
      delete_bst(now->right);
      delete now;
    }
  }

  bool find(int x) {
    BstNode *now = root_ptr;
    while (now && now->key != x) {
      now = now->get_child(x);
    }
    return now != nullptr;
  }

  void insert(int x) {
    int level = 1;
    if (root_ptr == nullptr) {
      root_ptr = new BstNode(x);
    } else {
      BstNode *now = root_ptr;
      while (now != nullptr && now->key != x) {
        ++level;
        if (now->key < x && now->right == nullptr) {
          now->right = new BstNode(x);
          break;
        }
        if (now->key > x && now->left == nullptr) {
          now->left = new BstNode(x);
          break;
        }
        now = now->get_child(x);
      }
    }
    bst_height = std::max(bst_height, level);
  }

  void erase(int x) {
    if (!find(x)) {
      return;
    }
    BstNode *now = root_ptr;
    BstNode *parent = nullptr;
    while (now && now->key != x) {
      parent = now;
      now = now->get_child(x);
    }
    if (now->left == nullptr) {
      if (!parent) {
        root_ptr = now->right;
      }
      if (parent && parent->key > now->key) {
        parent->left = now->right;
      }
      if (parent && parent->key < now->key) {
        parent->right = now->right;
      }
      delete now;
      return;
    }
    if (now->right == nullptr) {
      if (!parent) {
        root_ptr = now->left;
      }
      if (parent && parent->key > now->key) {
        parent->left = now->left;
      }
      if (parent && parent->key < now->key) {
        parent->right = now->left;
      }
      delete now;
      return;
    }
    BstNode *min_right_node = now->right;
    while (min_right_node->left) {
      min_right_node = min_right_node->left;
    }
    int new_key = min_right_node->key;
    erase(new_key);
    now->key = new_key;
  }

  bool is_leaf(BstNode* node) {
    return !node->left && !node->right;
  }

  int calculate_subtrees(BstNode* node) {
    if (!node) {
        return 0;
    }
    if (is_leaf(node)) {
        ++node->subtree_height;
        return node->subtree_height;
    }
    node->subtree_height = std::max(calculate_subtrees(node->right), calculate_subtrees(node->left)) + 1;
    return node->subtree_height;
  }

  void check_balance(BstNode* now)  {
    if (now->left) {
        check_balance(now->left);
    }
    int balance = 0;
    if (now->left) {
        balance -= now->left->subtree_height;
    }
    if (now->right) {
        balance += now->right->subtree_height;
    }
    if (std::abs(balance) > 1) {
        balanced = false;
    }
    if (now->right) {
        check_balance(now->right);
    }
  }

  bool is_balanced() {
    calculate_subtrees(root_ptr);
    check_balance(root_ptr);
    return balanced;
  }

  BstNode* get_root() {
    return root_ptr;
  }

private:
  BstNode *root_ptr;
  int bst_height = 0;
  bool balanced = true;
};

int main() {
  BST bst;
  int n;
  std::cin >> n;
  while (n != 0) {
    bst.insert(n);
    std::cin >> n;
  }
  bool balanced = bst.is_balanced();
  if (balanced) {
    std::cout << "YES";
    return 0;
  }
  std::cout << "NO";
}