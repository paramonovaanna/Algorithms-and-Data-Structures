#include <iostream>
#include <string>

void print_binary(std::string result, int now_length, int now_ones, int N, int K) {
    if (now_ones > K || (now_ones < K && (N - now_length) < K - now_ones)) {
        return;
    }
    if (now_length == N && now_ones == K) {
        std::cout << result << "\n";
        return;
    }
    print_binary(result + "0", now_length + 1, now_ones, N, K);
    print_binary(result + "1", now_length + 1, now_ones + 1, N, K);
}

void binary(int N, int K) {
    print_binary("", 0, 0, N, K);
}

int main() {
    int N, K;
    std::cin >> N >> K;
    binary(N, K);
}