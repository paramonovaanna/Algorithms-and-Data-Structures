#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<std::pair<int, bool>>>;


void dfs_orient(int now, std::vector<bool> &visited, Graph &graph, std::vector<int> &reversed_order) {
    visited[now] = true;
    for (std::pair<int, bool> &edge : graph[now]) {
        if (!visited[edge.first]) {
            edge.second = false;
            dfs_orient(edge.first, visited, graph, reversed_order);
        }
    }
    reversed_order.push_back(now);
}

void dfs_color(int now, int color, std::vector<int> &colored, const Graph &graph) {
    colored[now] = color;
    for (const auto& [vertex, edge] : graph[now]) {
        if (edge == true && !colored[vertex]) {
            dfs_color(vertex, color, colored, graph);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);
    std::vector<std::pair<int, int>> edges;

    for (size_t i = 0; i != m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        --v1;
        --v2;
        graph[v1].push_back(std::pair(v2, true));
        graph[v2].push_back(std::pair(v1, true));

        edges.push_back(std::pair(v1, v2));
    }

    std::vector<bool> visited(n);
    std::vector<int> reversed_order;
    for (size_t i = 0; i != n; ++i){
        if (!visited[i]) {
            dfs_orient(i, visited, graph, reversed_order);
        }
    }

    int color = 0;
    std::vector<int> colored(n);
    for (size_t i = 0; i != n; ++i) {
        if (!colored[reversed_order[n - i - 1]]) {
            ++color;
            dfs_color(reversed_order[n - i - 1], color, colored, graph);
        }
    }

    std::vector<int> bridges;
    for (size_t i = 0; i != m; ++i) {
        if (colored[edges[i].first] != colored[edges[i].second]) {
            bridges.push_back(i + 1);
        }
    }

    std::cout << bridges.size() << std::endl;

    for (int bridge : bridges) {
        std::cout << bridge << std::endl;
    }
}