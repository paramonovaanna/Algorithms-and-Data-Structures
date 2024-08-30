#include <iostream>
#include <vector>

std::vector<int> calculate_factorials(int N) {
    std::vector<int> factorials(N + 1);
    factorials[0] = 1;
    for (size_t i = 1; i < N + 1; ++i) {
        factorials[i] = factorials[i - 1] * i;
    }
    return factorials;
}


void print_permutation(int N, int K, std::vector<int> factorials) {
    --K;
    std::vector<int> numbers;
    for (int i = 1; i < N + 1; ++i) {
        numbers.push_back(i);
    }

    for (int i = N - 1; i >= 0; --i) {
        int element = K / factorials[i];
        std::cout << numbers[element] << " ";
        numbers.erase(numbers.begin() + element);
        K = K % factorials[i];
    }
}

int main() {
    int N, K;
    std::cin >> N >> K;
    std::vector<int> factorials = calculate_factorials(N);
    print_permutation(N, K, factorials);
}