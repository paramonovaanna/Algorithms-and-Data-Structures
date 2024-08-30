#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<bool>>;

void floyd(int n, Graph& graph) {
    for (size_t k = 0; k < n; ++k) {
        for (size_t from = 0; from < n; ++from) {
            for (size_t to = 0; to < n; ++to) {
                graph[from][to] = graph[from][to] || (graph[from][k] && graph[k][to]);
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    Graph graph(n, std::vector<bool>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            bool is_edge;
            std::cin >> is_edge;
            graph[i][j] = is_edge;
        }
    }
    floyd(n, graph);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cout << graph[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}