#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>
#include <set>

struct Road {
    int vertex;
    int time;
    int64_t limit_weight;
};

const int MAX_TIME = 1440;
const int64_t MAX_CUPS = 10000000;
const int64_t TRUCK_WEIGHT = 3 * 1e6;
const int64_t CUP_WEIGHT = 100;

const int INF = std::numeric_limits<int>::max() / 2;

using Graph = std::vector<std::vector<Road>>;

void dijkstra(int start, int64_t weight, int n, const Graph& graph, std::vector<int>& min_distances) {
    min_distances[0] = 0;

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
        for (auto [vertex, time, limit_weight] : graph[nearest.second]) {
            if (limit_weight < weight) {
                continue;
            }
            if (!visited[vertex] && min_distances[vertex] > nearest.first + time) {
                min_distances[vertex] = nearest.first + time;
                vertexes_set.insert({min_distances[vertex], vertex});
            }
        }
    }
}


bool possible_amount(int64_t cups, const Graph& graph) {
    int64_t weight = cups * CUP_WEIGHT + TRUCK_WEIGHT;

    int n = graph.size();
    std::vector<int> min_distances(n, INF);
    dijkstra(0, weight, n, graph, min_distances);

    return min_distances[n - 1] <= MAX_TIME;
}

int64_t binary_search(int64_t left, int64_t right, const Graph& graph) {
    while (right - left > 1) {
        int64_t middle = (left + right) / 2;
        if (possible_amount(middle, graph)) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return left;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);
    for (size_t i = 0; i < m; ++i) {
        int v1, v2, time;
        int64_t max_weight;
        std::cin >> v1 >> v2 >> time >> max_weight;
        --v1;
        --v2;
        graph[v1].push_back(Road{v2, time, max_weight});
        graph[v2].push_back(Road{v1, time, max_weight});
    }

    int64_t answer = binary_search(0, MAX_CUPS * 2, graph);
    std::cout << std::min(answer, MAX_CUPS);
}