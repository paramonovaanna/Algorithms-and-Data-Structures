#include <iostream>
#include <vector>

void print_binary(std::vector<int> result, int now_length, int K, std::vector<int> available) {
    if (now_length == K) {
        for (int n : result) {
            std::cout << n << " ";
        }
        std::cout << "\n";
        return;
    }
    if (K - now_length > available.size()) {
        return;
    }
    for (size_t i = 0; i < available.size(); ++i) {
        std::vector<int> new_result = result;
        new_result.push_back(available[i]);
        print_binary(new_result, now_length + 1, K, std::vector<int>(available.begin() + i + 1, available.end()));
    }
}

void binary(int N, int K) {
    std::vector<int> available;
    for (int n = 1; n < N + 1; ++n) {
        available.push_back(n);
    }
    std::vector<int> now;
    print_binary(now, 0, K, available);
}

int main() {
    int N, K;
    std::cin >> N >> K;
    binary(N, K);
}