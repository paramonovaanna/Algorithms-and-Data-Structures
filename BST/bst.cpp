#include <iostream>

struct BstNode {
  int key;
  BstNode* left;
  BstNode* right;
  BstNode(int key) : key(key), left(nullptr), right(nullptr){}

  BstNode* get_child(int value) {
    if (key < value) {
        return right;
    }
    return left;
  }
};

class BST {
public:
    BST() {
        root_ptr = nullptr;
    };

    ~BST() {
        delete_bst(root_ptr);
    }

    void delete_bst(BstNode* now) {
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
        if (parent->key > now->key) {
            parent->left = now->left;   
        } else {
            parent->right = now->right;   
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

  int get_bst_height() { return bst_height; }

private:
  BstNode* root_ptr;
  int bst_height = 0;
};

int main() {
  BST bst;
  int n;
  std::cin >> n;
  while (n != 0) {
    bst.insert(n);
    std::cin >> n;
  }
  std::cout << bst.get_bst_height();
}