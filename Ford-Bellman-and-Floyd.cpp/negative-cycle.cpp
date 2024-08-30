#include <algorithm>
#include <iostream>
#include <vector>

struct Edge{
    size_t from;
    size_t to;
    int weight;
};

const int INF = 1e9;

int ford_bellman(int n, const std::vector<Edge> &edges, std::vector<int> &parents) {
    std::vector<int> min_distances(n, INF);

    bool is_changed = false;
    for (size_t i = 0; i < n ; ++i) {
        is_changed = false;
        for (auto [from, to, weight] : edges) {
            if (min_distances[from] + weight < min_distances[to]) {
                min_distances[to] = min_distances[from] + weight;
                parents[to] = from;
                is_changed = true;
            }
        }
        if (!is_changed) {
            break;
        }
    }
    int vertex = -1;
    for (auto [from, to, weight] : edges) {
            if (min_distances[from] + weight < min_distances[to]) {
                min_distances[to] = min_distances[from] + weight;
                vertex = to;
            }
        }
    return vertex;
}

std::vector<int> find_cycle(int vertex, const std::vector<int> &parents) {
    std::vector<int> probably_cycle;
    std::vector<bool> used(parents.size());
    int now = vertex;
    for (size_t i = 0; i < parents.size(); ++i) {
        probably_cycle.push_back(now);
        if (used[now]) {
            break;
        }
        used[now] = true;
        now = parents[now];
    }
    std::vector<int> cycle;
    bool repeated = false;
    for (int vertex : probably_cycle) {
        if (vertex == now) {
            if (repeated) {
                cycle.push_back(vertex);
                break;
            }
            repeated = true;
        }
        if (repeated) {
            cycle.push_back(vertex);
        }
    }
    if (cycle[0] != cycle.back()) {
        cycle.push_back(cycle[0]);
    }
    return cycle;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Edge> edges;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            int weight;
            std::cin >> weight;
            edges.push_back(Edge{i, j, weight});
        }
    }
    std::vector<int> parents(n, -1);
    int vertex = ford_bellman(n, edges, parents);
    if (vertex == -1) {
        std::cout << "NO";
        return 0;
    }
    std::cout << "YES" << '\n';
    std::vector<int> cycle = find_cycle(vertex, parents);
    std::cout << cycle.size() << '\n';
    std::reverse(cycle.begin(), cycle.end());
    for (int vertex : cycle) {
        std::cout << vertex + 1 << ' ';
    }
}