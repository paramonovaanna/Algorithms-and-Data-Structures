#include <iostream>
#include <string>

void print_binary(std::string result, int now_length, int N, std::string available) {
    if (now_length == N) {
        std::cout << result << "\n";
        return;
    }
    for (size_t i = 0; i < available.length(); ++i) {
        print_binary(result + available[i], now_length + 1, N, available.substr(0, i) + available.substr(i + 1));
    }
}

void binary(int N) {
    std::string available = "123456789";
    print_binary("", 0, N, available.substr(0, N));
}

int main() {
    int N;
    std::cin >> N;
    binary(N);
}