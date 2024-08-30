#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>
#include <set>
#include <limits>

using Graph = std::vector<std::vector<std::pair<int, int>>>;

const int INF = std::numeric_limits<int>::max() / 2;

void dijkstra(int start, int n, const Graph& graph, std::vector<int>& min_distances, std::vector<int> &parents) {
    min_distances[start] = 0;

    std::set<std::pair<int, int>> vertexes_set;
    vertexes_set.insert({0, start});

    std::vector<bool> visited(n);

    for (int i = 0; i < n; ++i) {
        if (vertexes_set.empty())
            return;
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
                parents[vertex] = nearest.second;
            }
        }
    }
}

int main() {
    int n, start, finish;
    std::cin >> n >> start >> finish;
    --start;
    --finish;

    Graph graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int weight;
            std::cin >> weight;
            if (weight != -1) {
                graph[i].push_back({weight, j});
            }
        }
    }

    std::vector<int> min_distance(n, INF);
    std::vector<int> parents(n);

    dijkstra(start, n, graph,min_distance, parents);

    if (min_distance[finish] == INF) {
        std::cout << -1;
    } else {
        std::vector<int> result_path;
        int now = finish;
        while (now != start) {
            result_path.push_back(now);
            now = parents[now];
        }
        result_path.push_back(now);
        std::reverse(result_path.begin(), result_path.end());
        for (int vertex : result_path) {
            std::cout << vertex + 1 << ' ';
        }
    }
}
