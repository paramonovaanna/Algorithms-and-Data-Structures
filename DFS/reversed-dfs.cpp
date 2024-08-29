#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void dfs(int now, std::vector<bool>& visited, const Graph& graph) {
    visited[now] = true;
    for (int neighb : graph[now]) {
        if (!visited[neighb]) {
            dfs(neighb, visited, graph);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph graph(n);

    for (size_t i = 0; i != m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;

        --v1;
        --v2;

        graph[v2].push_back(v1);
    }

    std::vector<bool> visited(n);

    dfs(0, visited, graph);

    std::cout << 1 << ' ';

    for (size_t i = 1; i != n; ++i) {
        if (visited[i]) {
            std::cout << i + 1 << ' ';
        }
    }
}

