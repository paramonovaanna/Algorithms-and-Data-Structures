#include <iostream>
#include <string>
#include <vector>

struct Node {
    bool bit;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node() = default;

    Node(Node* parent, bool bit): parent{parent}, bit{bit} {
    }

    bool NoChildren() {
        return left == nullptr && right == nullptr;
    }
};

class HaffmansTree {
public:
    HaffmansTree() {
        root = new Node();
    };

    void build(const std::string& description) {
        Node* current_node = root;
        bool up = false;
        for (size_t i = 0; i < description.size(); ++i) {
            if (description[i] == 'D') {
                current_node->left = new Node(current_node, 0);
                current_node = current_node->left;
                continue;
            }
            ++leaves_amount;
            up = true;
            while (current_node->bit == 1 && current_node->parent != nullptr) {
                current_node = current_node->parent;
            }
            if (current_node->parent == nullptr && !current_node->NoChildren()) {
                continue;
            }
            current_node = current_node->parent;
            current_node->right = new Node(current_node, 1);
            current_node = current_node->right;
        }
        ++leaves_amount;
    }

    void in_order(Node* now, std::string code)  {
        if (now->NoChildren()) {
            std::cout << code << '\n';
            return;
        }
        if (now->left) {
            in_order(now->left, code + '0');
        }
        if (now->right) {
            in_order(now->right, code + '1');
        }
    }

    void get_codes() {
        std::cout << leaves_amount << "\n";
        in_order(root, "");
    }

private:
    Node* root;
    int leaves_amount = 0;
};


int main() {
    int n;
    std::cin >> n;
    for (size_t i = 0; i < n; ++i) {
        std::string tree_description;
        std::cin >> tree_description;
        HaffmansTree tree;
        tree.build(tree_description);
        tree.get_codes();
    }
}