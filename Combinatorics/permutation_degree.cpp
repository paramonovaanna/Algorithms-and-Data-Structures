#include <iostream>
#include <numeric>
#include <vector>

void dfs(int now, int cycle_length, std::vector<bool>& visited, std::vector<int>& cycles_lengths, const std::vector<int>& permutation) {
    if (visited[permutation[now]]) {
        cycles_lengths.push_back(cycle_length);
        return;
    }
    visited[permutation[now]] = true;
    dfs(permutation[now], cycle_length + 1, visited, cycles_lengths, permutation);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> permutation(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> permutation[i];
        --permutation[i];
    }

    std::vector<bool> visited(n);
    std::vector<int> cycles_lengths;
    for (size_t i = 0; i < n; ++i) {
        if (!visited[i]) {
            visited[i] = true;
            dfs(i, 1, visited, cycles_lengths, permutation);
        }
    }

    int degree = 1;
    for (int cycle_length : cycles_lengths) {
        degree *= cycle_length / std::gcd(degree, cycle_length);
    }
    std::cout << degree;
}