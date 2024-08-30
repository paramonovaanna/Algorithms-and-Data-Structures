#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <limits>

struct Trip {
    int vertex;
    int time_go;
    int time_travel;
};

using Graph = std::vector<std::vector<Trip>>;

int INF = std::numeric_limits<int>::max() / 2;

void dijkstra(int start, int previous_time, int n, std::vector<int> &min_distances, const Graph& graph) {
    std::set<std::pair<int, int>> vertexes_set;
    vertexes_set.insert({previous_time, start});

    min_distances[start] = previous_time;

    std::vector<bool> visited(n);

    for (size_t i = 0; i < n && !vertexes_set.empty(); ++i) {
        std::pair<int, int> nearest = *vertexes_set.begin();
        vertexes_set.erase(vertexes_set.begin());
        while (visited[nearest.second]) {
            if (vertexes_set.empty())
                return;
            nearest = *vertexes_set.begin();
            vertexes_set.erase(vertexes_set.begin());
        }
        visited[nearest.second] = true;
        for (auto [vertex, time_go, time_travel] : graph[nearest.second]) {
            int new_distance = nearest.first + (time_go - nearest.first % time_go) % time_go + time_travel;
            if (!visited[vertex] && min_distances[vertex] > new_distance) {
                min_distances[vertex] = new_distance;
                vertexes_set.insert({min_distances[vertex], vertex});
            }
        }
    }
}


int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);
    for (size_t i = 0; i < m; ++i) {
        int v1, time_go;
        int v2, time_travel;
        std::cin >> v1 >> v2 >> time_go >> time_travel;
        --v1;
        --v2;
        graph[v1].push_back(Trip{v2, time_go, time_travel});
    }

    int k;
    std::cin >> k;
    std::vector<int> places(k);
    for (size_t i = 0; i < k; ++i) {
        std::cin >> places[i];
        --places[i];
    }

    int result = 0;
    for (size_t i = 1; i < k; ++i) {
        std::vector<int> min_distances(n, INF);
        dijkstra(places[i - 1], result, n, min_distances, graph);
        if (min_distances[places[i]] == INF) {
            std::cout << -1;
            return 0;
        }
        result = min_distances[places[i]];
    }
    std::cout << result;
}