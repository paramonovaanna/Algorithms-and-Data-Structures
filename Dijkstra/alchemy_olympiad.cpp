#include <iostream>
#include <vector>
#include <limits>
#include <set>

using Graph = std::vector<std::vector<std::pair<int, int>>>;

const int INF = std::numeric_limits<int>::max() / 2;

void dijkstra(int start, int n, const Graph& graph, std::vector<int>& min_distances) {
    min_distances[start] = 0;

    std::set<std::pair<int, int>> vertexes_set;
    vertexes_set.insert({0, start});

    std::vector<bool> visited(n);

    for (int i = 0; i < n; ++i) {
        if (vertexes_set.empty())
            return;
        std::pair<int, int> nearest = *vertexes_set.begin();
        vertexes_set.erase(vertexes_set.begin());
        while (visited[nearest.second]) {
            if (vertexes_set.empty())
                return;
            nearest = *vertexes_set.begin();
            vertexes_set.erase(vertexes_set.begin());
        }
        visited[nearest.second] = true;
        for (auto [distance, vertex] : graph[nearest.second]) {
            if (!visited[vertex] && min_distances[vertex] > nearest.first + distance) {
                min_distances[vertex] = nearest.first + distance;
                vertexes_set.insert({min_distances[vertex], vertex});
            }
        }
    }
}

int main() {
    int n, m, t;
    std::cin >> n >> m >> t;

    int capital;
    std::cin >> capital;
    --capital;

    std::vector<int> towns(t);
    for (size_t i = 0; i < t; ++i) {
        std::cin >> towns[i];
        --towns[i];
    }

    Graph graph(n);
    for (size_t i = 0; i < m; ++i) {
        int v1, v2, time;
        std::cin >> v1 >> v2 >> time;
        --v1;
        --v2;
        graph[v1].push_back({time, v2});
        graph[v2].push_back({time, v1});
    }

    std::vector<int> min_distance(n, INF);

    dijkstra(capital, n, graph, min_distance);

    std::set<std::pair<int, int>> result;
    for (int town : towns) {
        result.insert({min_distance[town], town});
    }
    for (auto [time, town] : result) {
        std::cout << town + 1 << ' ' << time << '\n';
    }
}