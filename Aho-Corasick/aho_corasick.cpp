#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

const int ALPHABET_SIZE = 26;

struct Node {
    std::vector<size_t> words;
    int suf_link;
    int term;
    std::vector<int> go;

    Node(): suf_link{-1}, term{-1} {
        go.resize(ALPHABET_SIZE, -1);
    }
};

class AhoCorasick {
public:
    AhoCorasick() {
        trie.resize(1);
    }

    void add_word(const std::string& word, size_t index) {
        size_t now = 0;
        for (char symbol : word) {
            symbol -= 'a';
            if (trie[now].go[symbol] == -1) {
                trie.push_back(Node());
                trie[now].go[symbol] = trie.size() - 1;
            }
            now = trie[now].go[symbol];
        }
        trie[now].words.push_back(index);
    }

    void build() {
        trie[0].suf_link = 0;
        for (size_t symbol = 0; symbol < ALPHABET_SIZE; ++symbol) {
            if (trie[0].go[symbol] != -1) {
                continue;
            }
            trie[0].go[symbol] = 0;
        }

        std::queue<int> nodes_queue;
        nodes_queue.push(0);

        while (!nodes_queue.empty()) {
            int now = nodes_queue.front();
            nodes_queue.pop();
            for (size_t symbol = 0; symbol < ALPHABET_SIZE; ++symbol) {
                int child = trie[now].go[symbol];
                // Если ребенок уже встречался, пропускаем (нужно для корня, ведь сначала все его несуществующие дети вернутся в корень по go)
                if (trie[child].suf_link != -1) {
                    continue;
                }
                // Calculating suff_links for child children (to avoid storing parent info)
                if (now == 0) {
                    trie[child].suf_link = 0; // Root children suff_links go to root
                } else {
                    trie[child].suf_link = trie[trie[now].suf_link].go[symbol];
                }
                // Calculating go for child's children
                for (size_t child_symbol = 0; child_symbol < ALPHABET_SIZE; ++child_symbol) {
                    if (trie[child].go[child_symbol] != -1) {
                        continue;
                    }
                    trie[child].go[child_symbol] = trie[trie[child].suf_link].go[child_symbol];
                }
                //Calculating term for child's children
                if (trie[trie[child].suf_link].words.size() > 0) {
                    trie[child].term = trie[child].suf_link;
                } else {
                    trie[child].term = trie[trie[child].suf_link].term;
                }
                nodes_queue.push(child);
            }
        }
    }

    std::vector<std::vector<size_t>> get_indexes(const std::string& string, int n) {
        std::vector<std::vector<size_t>> word_indexes(n);
        size_t current_node = 0;
        for (size_t i = 0; i < string.size(); ++i) {
            char letter = string[i];
            current_node = trie[current_node].go[letter - 'a'];
            for (size_t word : trie[current_node].words) {
                word_indexes[word].push_back(i + 1);
            }

            size_t now = current_node;
            while (trie[now].term != -1) {
                now = trie[now].term;
                for (size_t word : trie[now].words) {
                    word_indexes[word].push_back(i + 1);
                }   
            }
        }
        return word_indexes;
    }

private:
    std::vector<Node> trie;
};

int main() {
    AhoCorasick automat;

    std::string string;
    std::cin >> string;
    int n;
    std::cin >> n;
    std::vector<int> lengths(n);
    for (size_t i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        lengths[i] = word.size();
        automat.add_word(word, i);
    }
    automat.build();

    std::vector<std::vector<size_t>> answer = automat.get_indexes(string, n);
    for (size_t i = 0; i < n; ++i) {
        std::cout << answer[i].size() << ' ';
        for (size_t index : answer[i]) {
            std::cout << index - lengths[i] + 1 << ' ';
        }
        std::cout << '\n';
    }
}
