#include <iostream>
#include <vector>
#include <set>
#include <limits>

struct Trip {
    int vertex;
    int time_go;
    int time_arrive;
};

using Graph = std::vector<std::vector<Trip>>;

const int INF = std::numeric_limits<int>::max() / 2;

void dijkstra(int start, int n, std::vector<int> &min_distances, const Graph& graph) {
    std::set<std::pair<int, int>> vertexes_set;
    vertexes_set.insert({0, start});

    min_distances[start] = 0;

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
        for (auto [vertex, time_go, time_arrive] : graph[nearest.second]) {
            if (!visited[vertex] && nearest.first <= time_go) {
                if (min_distances[vertex] > time_arrive) {
                    min_distances[vertex] = time_arrive;
                    vertexes_set.insert({min_distances[vertex], vertex});
                }
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    int start, finish;
    std::cin >> start >> finish;
    --start;
    --finish;

    int trips;
    std::cin >> trips;

    Graph graph(n);
    for (size_t i = 0; i < trips; ++i) {
        int v1, v2;
        int time_go, time_arrive;

        std::cin >> v1 >> time_go >> v2 >> time_arrive;
        --v1;
        --v2;

        graph[v1].push_back(Trip{v2, time_go, time_arrive});
    }

    std::vector<int> min_distances(n, INF);
    dijkstra(start, n, min_distances, graph);

    if (min_distances[finish] == INF) {
        std::cout << -1;
    } else {
        std::cout << min_distances[finish];
    }
}