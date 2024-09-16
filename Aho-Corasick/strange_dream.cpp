#include <iostream>
#include <unordered_map>
#include <vector>

struct Node {
    std::unordered_map<char, int> children;
    char symbol_from = ' ';

    Node() = default;
    Node(char symbol, size_t parent): symbol_from{symbol} {}
};

class Dictionary {
public:
    Dictionary() {
        trie.resize(1);
        requests_nodes[1] = 0;
        unique_words_amount = 0;
    }

    void add_symbol(size_t request, size_t p, char symbol) {
        size_t node_index = requests_nodes[p];
        if (trie[node_index].children.count(symbol) > 0) {
            requests_nodes[request] = trie[node_index].children[symbol];
            return;
        }
        trie.push_back(Node(symbol, node_index));
        trie[node_index].children[symbol] = trie.size() - 1;
        requests_nodes[request] = trie.size() - 1;
        ++unique_words_amount;
    }

    int get_unique_words_amount() {
        return unique_words_amount;
    }

private:
    std::vector<Node> trie;
    std::unordered_map<size_t, size_t> requests_nodes;
    int unique_words_amount;
};


int main() {
    Dictionary dictionary;
    int n;
    std::cin >> n;
    for (size_t i = 1; i <= n; ++i) {
        size_t p_i;
        char symbol;
        std::cin >> p_i >> symbol;
        dictionary.add_symbol(i + 1, p_i, symbol);
        std::cout << dictionary.get_unique_words_amount() << '\n';
    }
}