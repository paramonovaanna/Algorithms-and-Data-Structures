#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

bool dfs(int now, std::vector<int> &colored, const Graph &graph, std::vector<int> &reverse_toposort) {
    colored[now] = 1;
    bool cycle_exists = false;
    for (int neighb : graph[now]) {
        if (colored[neighb] == 1) {
            cycle_exists = true;
        } else if (!colored[neighb]) {
            cycle_exists = dfs(neighb, colored, graph, reverse_toposort);
        }
        if (cycle_exists) {
            return cycle_exists;
        }
    }
    colored[now] = 2;
    reverse_toposort.push_back(now);
    return cycle_exists;
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
        graph[v1].push_back(v2);
    }

    std::vector<int> colored(n);
    std::vector<int> reversed_toposort;
    bool cycle_exists;
    for (size_t i = 0; i != n; ++i) {
        if (!colored[i]) {
            cycle_exists = dfs(i, colored, graph, reversed_toposort);
        }
        if (cycle_exists) {
            break;
        }
    }

    if (cycle_exists) {
        std::cout << -1;
    } else {
        for (size_t i = 0; i != n; ++i) {
            std::cout << reversed_toposort[n - i - 1] + 1 << ' ';
        }
    }
}