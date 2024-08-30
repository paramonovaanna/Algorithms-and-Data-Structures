#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> calculate_factorials(int N) {
    std::vector<int> factorials(N + 1);
    factorials[0] = 1;
    for (size_t i = 1; i < N + 1; ++i) {
        factorials[i] = factorials[i - 1] * i;
    }
    return factorials;
}


void print_placement_number(int N, int K, const std::vector<int>& placement, const std::vector<int>& factorials) {
    std::vector<int> numbers(N);
    for (size_t i = 0; i < N; ++i) {
        numbers[i] = i + 1;
    }

    int result = 0;
    for (size_t i = 0; i < K; ++i) {
        int index = find(numbers.begin(), numbers.end(), placement[i]) - numbers.begin();
        result += index * factorials[N - i - 1] / factorials[N - K];
        numbers.erase(numbers.begin() + index);
    }
    std::cout << result + 1;
}


int main() {
    int N, K;
    std::cin >> N >> K;
    std::vector<int> placement(K);
    for (size_t i = 0; i < K; ++i) {
        std::cin >> placement[i];
    }
    std::vector<int> factorials = calculate_factorials(N);
    print_placement_number(N, K, placement, factorials);
}