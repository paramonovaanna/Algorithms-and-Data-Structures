#include <iostream>
#include <cstdint>
#include <vector>
#include <set>

using Graph = std::vector<std::vector<std::pair<int64_t, int64_t>>>;

const int64_t INF = 1e17;

void dijkstra(int64_t start, int n, const Graph& graph, std::vector<int64_t>& min_distances) {

    min_distances[start] = 0;

    std::set<std::pair<int64_t, int64_t>> vertexes_set;
    vertexes_set.insert({0, start});

    std::vector<bool> visited(n);

    for (int i = 0; i < n && !vertexes_set.empty(); ++i) {
        std::pair<int64_t, int64_t> nearest = *vertexes_set.begin();
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
    int64_t n, k;
    std::cin >> n >> k;
    Graph graph(n);

    for (size_t i = 0; i < k; ++i) {
        int v1, v2, distance;
        std::cin >> v1 >> v2 >> distance;
        --v1;
        --v2;
        graph[v1].push_back({ distance, v2});
        graph[v2].push_back({distance, v1});
    }

    int64_t start, finish;
    std::cin >> start >> finish;
    --start;
    --finish;

    std::vector<int64_t> min_distance(n, INF);

    dijkstra(start, n, graph,min_distance);

    if (min_distance[finish] == INF) {
        std::cout << -1;
    } else {
        std::cout << min_distance[finish];
    }
}
