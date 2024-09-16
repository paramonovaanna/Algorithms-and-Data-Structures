#include <iostream>
#include <vector>
#include <map>

struct Node {
    bool terminal = false;
    std::map<char, int> children;
    int parent_index = 0;
    int words = 0;
};

class Dictionary {
public:
    Dictionary() {
        trie.resize(1);
    }

    void add_word(const std::string& word) {
        size_t current = 0;
        for (char symbol : word) {
            if (trie[current].children.count(symbol) == 0) {
                trie.push_back(Node());
                trie.back().parent_index = current;
                trie[current].children[symbol] = trie.size() - 1;
            }
            current = trie[current].children[symbol];
        }
        trie[current].terminal = true;
        update_words(current);
    }

    std::string get_word(int k) {
        int word_number = 0;
        std::string k_word;
        size_t index = 0;
        while (word_number < k) {
            if (trie[index].terminal) {
                ++word_number;
                if (word_number == k) {
                    break;
                }
            }
            for (auto child : trie[index].children) {
                if (trie[child.second].words + word_number >= k) {
                    index = child.second;
                    k_word += child.first;
                    break;
                }
                word_number += trie[child.second].words;
            }
        }
        while (!trie[index].terminal) {
            k_word += trie[index].children.begin()->first;
            index = trie[index].children.begin()->second;
        }
        return k_word;
    }

private:
    std::vector<Node> trie;

    void update_words(size_t current_index) {
        ++trie[current_index].words;
        if (current_index == 0) {
            return;
        }
        return update_words(trie[current_index].parent_index);
    }
};

int main() {
    Dictionary dictionary;
    int n;    
    std::cin >> n;
    for (size_t i = 0; i < n; ++i) {
        int command;
        std::cin >> command;
        if (command == 1) {
            std::string s;
            std::cin >> s;
            dictionary.add_word(s);
        } else if (command == 2) {
            int k;
            std::cin >> k;
            std::cout << dictionary.get_word(k) << '\n';
        }
    }
}