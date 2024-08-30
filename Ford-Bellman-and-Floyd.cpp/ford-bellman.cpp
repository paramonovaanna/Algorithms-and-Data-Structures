#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

const int INF = 1e6;

std::vector<int> ford_bellman(int n, int start) {
    std::vector<int> min_distances(n, INF);
    min_distances[0] = start;
    for (size_t i = 0; i < n; ++i) {
        bool is_changed = false;
        for (size_t u = 0; u < n; ++u) {
            for (size_t v = 0; v < u; ++v) {
                int weight = (179 * (v + 1) + 719 * (u + 1)) % 1000 - 500;
                if (min_distances[v] + weight < min_distances[u]) {
                    min_distances[u] = min_distances[v] + weight;
                    is_changed = true;
                }
            }
        }
        if (!is_changed) {
            break;
        }
    }
    return min_distances;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> min_distances = ford_bellman(n, 0);
    std::cout << min_distances[n - 1];
}