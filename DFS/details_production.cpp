#include <cstdint>
#include <iostream>
#include <vector>


using Graph = std::vector<std::vector<int>>;

long long dfs(int now, std::vector<bool> &visited, std::vector<int> &order, const Graph &graph, const std::vector<long long> &times) {
    visited[now] = true;
    long long time = times[now];
    for (int neighb : graph[now]) {
        if (!visited[neighb]) {
            time += dfs(neighb, visited, order, graph, times);
        }
    }
    order.push_back(now);
    return time;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<long long> times(n);
    for (size_t i = 0; i != n; ++i) {
        std::cin >> times[i];
    }

    Graph graph(n);
    for (size_t i = 0; i != n; ++i) {
        int k;
        std::cin >> k;
        for (size_t j = 0; j != k; ++j) {
            int detail;
            std::cin >> detail;
            --detail;
            graph[i].push_back(detail);
        }
    }

    std::vector<bool> visited(n);
    std::vector<int> order;

    int64_t time = dfs(0, visited, order, graph, times);

    std::cout << time << ' ' << order.size() << std::endl;

    for (size_t i = 0; i != order.size(); ++i) {
        std::cout << order[i] + 1 << ' ';
    }
}