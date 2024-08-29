#include <iostream>
#include <vector>
#include <algorithm>

using Graph = std::vector<std::vector<int>>;

void dfs(int now, std::vector<bool>& visited, const Graph& graph) {
    visited[now] = true;

    for (size_t i = 0; i != graph.size(); ++i) {
        if (!visited[i] && graph[now][i]) {
            dfs(i, visited, graph);
        }
    }
}

void dfs2(int now, std::vector<bool>& visited, Graph& graph, std::vector<int>& reversed_order) {
    visited[now] = true;

    for (size_t i = 0; i != visited.size(); ++i) {
        if (!visited[i] && graph[now][i]) {
            dfs2(i, visited, graph, reversed_order);
            graph[now][i]--;
        }
    }

    reversed_order.push_back(now);
}

void dfs3(int now, std::vector<bool>& visited, std::vector<std::vector<std::pair<int, int>>>& gP, std::vector<int>& r, std::vector<std::pair<int, int>>& answer) {
    visited[now] = true;

    for (const auto [index, output] : gP[now]) {
        if (!visited[output]) {
            dfs3(output, visited, gP, r, answer);
            answer[index] = {now, output};
        }
    }

    r.push_back(now);
}

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n, std::vector<int>(n));
    std::vector<std::vector<std::pair<int, int>>> gP(n);
    std::vector<std::pair<int, int>> answer(m);

    for (size_t i = 0; i != m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        --v1;
        --v2;

        graph[v1][v2]++;
        graph[v2][v1]++;
        gP[v1].push_back({i, v2});
        gP[v2].push_back({i, v1});
    }

    std::vector<bool> visited(n);
    std::vector<int> reversed_order;

    for (size_t i = 0; i != n; ++i) {
        if (!visited[i]) {
            dfs2(i, visited, graph, reversed_order);
        }
    }

    std::fill(visited.begin(), visited.end(), false);
    
    dfs(reversed_order.back(), visited, graph);

    for (const bool use : visited) {
        if (!use) {
            std::cout << 0 << std::endl;
            return 0;
        }
    }

    reversed_order.clear();
    std::fill(visited.begin(), visited.end(), false);

    for (size_t i = 0; i != n; ++i) {
        if (!visited[i]) {
            dfs3(i, visited, gP, reversed_order, answer);
        }
    }

    for (const int vertex : reversed_order) {
        for (const auto [index, output] : gP[vertex]) {
            if (answer[index] == std::pair{0, 0}) {
                answer[index] = {vertex, output};
            }
        }
    }

    for (const auto [vertex, output] : answer) {
        std::cout << vertex + 1 << " " << output + 1 << std::endl;
    }

    return 0;
}
