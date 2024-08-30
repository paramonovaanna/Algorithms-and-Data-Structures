#include <bitset>
#include <iostream>
#include <string>

void print_binary(size_t bits_count) {
    for (long long n = 0; n < (1 << bits_count); ++n) {
        std::string output = std::bitset<10>(n).to_string();
        std::cout << output.substr(10 - bits_count)<< "\n";
    }
}

int main() {
    int N;
    std::cin >> N;
    print_binary(N);
}