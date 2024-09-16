#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

const int ALPHABET_SIZE = 26;

struct Node {
    std::vector<size_t> words_ending_here;
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
        words_.push_back(word);
        size_t now = 0;
        for (char symbol : word) {
            symbol -= 'a';
            if (trie[now].go[symbol] == -1) {
                trie.push_back(Node());
                trie[now].go[symbol] = trie.size() - 1;
            }
            now = trie[now].go[symbol];
        }
        trie[now].words_ending_here.push_back(index);
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
                if (trie[trie[child].suf_link].words_ending_here.size() > 0) {
                    trie[child].term = trie[child].suf_link;
                } else {
                    trie[child].term = trie[trie[child].suf_link].term;
                }
                nodes_queue.push(child);
            }
        }
    }

    int get_substrs(const std::string& string, int n) {
        int words_met = 0;
        std::vector<bool> visited_nodes(trie.size());

        size_t current_node = 0;
        for (size_t i = 0; i < string.size(); ++i) {
            char letter = string[i];
            current_node = trie[current_node].go[letter - 'a'];
            for (size_t word : trie[current_node].words_ending_here) {
                ++words_met;
            }

            size_t now = current_node;
            visited_nodes[now] = true;
            while (trie[now].term != -1) {
                now = trie[now].term;
                if (visited_nodes[now]) {
                    continue;
                }
                for (size_t word : trie[now].words_ending_here) {
                    ++words_met;
                }
                visited_nodes[now] = true;
            }
        }
        return words_met - 1;
    }

    int get_pairs() {
        int answer = 0;
        for (size_t i = 0; i < words_.size(); ++i) {
            answer += get_substrs(words_[i], words_.size());
        }
        return answer;
    }

private:
    std::vector<Node> trie;
    std::vector<std::string> words_;
};

int main() {
    AhoCorasick automat;

    int n;
    std::cin >> n;
    for (size_t i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        automat.add_word(word, i);
    }
    automat.build();
    int answer = automat.get_pairs();
    std::cout << answer;
}
