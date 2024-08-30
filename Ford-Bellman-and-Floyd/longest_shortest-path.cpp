#include <iostream>
#include <vector>
#include <limits>

using Graph = std::vector<std::vector<int>>;

const int INF = std::numeric_limits<int>::max() / 2;

void floyd(int n, Graph& graph) {
    for (size_t k = 0; k < n; ++k) {
        for (size_t from = 0; from < n; ++from) {
            for (size_t to = 0; to < n; ++to) {
                graph[from][to] = std::min(graph[from][to], (graph[from][k] + graph[k][to]));
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    Graph graph(n, std::vector<int>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            int is_edge;
            std::cin >> is_edge;
            if (is_edge == 0 && i != j) {
                graph[i][j] = INF;
            }
            else {
                graph[i][j] = is_edge;
            }
        }
    }
    floyd(n, graph);
    int answer = 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (graph[i][j] == INF) {
                continue;
            } else {
                answer = std::max(answer, graph[i][j]);
            }
        }
    }
    std::cout << answer;
}