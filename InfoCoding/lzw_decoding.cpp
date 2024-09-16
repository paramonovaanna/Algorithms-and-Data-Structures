#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

std::string LZW_decode(std::vector<int> to_decode) {
    std::vector<std::string> dictionary;
    for (int i = 0; i < 128; ++i) {
        std::string symbol;
        symbol += char(i);
        dictionary.push_back(symbol);
    }

    std::string decoded;
    std::string new_word;

    decoded += to_decode[0];
    new_word += to_decode[0];
    size_t current_index = 1;
    while (current_index < to_decode.size()) {
        if (to_decode[current_index] >= dictionary.size()) {
            decoded += dictionary[to_decode[current_index - 1]] + dictionary[to_decode[current_index - 1]][0];
            new_word = dictionary[to_decode[current_index - 1]] + dictionary[to_decode[current_index - 1]][0];
        } else {
            decoded += dictionary[to_decode[current_index]];
            new_word += dictionary[to_decode[current_index]][0];
        }
        dictionary.push_back(new_word);
        new_word = dictionary[to_decode[current_index]];
        ++current_index;
    }
    return decoded;
}


int main() {
    int n;
    std::cin >> n;
    std::vector<int> to_decode(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> to_decode[i];
    }
    std::cout << LZW_decode(to_decode);
}