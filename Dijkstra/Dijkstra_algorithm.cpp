#include <climits>
#include <iostream>
#include <vector>
#include <set>


using Vertex = std::pair<int, int>;
using Graph = std::vector<std::vector<Vertex>>;

int INF = INT_MAX / 2;

int dijkstra(int n, int start, int finish, const Graph &graph) {
    std::set<Vertex> vertexes_set;
    vertexes_set.insert({0, start});

    std::vector<int> min_distances(n, INF);
    min_distances[start] = 0;

    while (!vertexes_set.empty()) {
        Vertex nearest = *vertexes_set.begin();
        vertexes_set.erase(*vertexes_set.begin());

        for (auto neighb : graph[nearest.second]) {
            if (min_distances[neighb.second] > min_distances[nearest.second] + neighb.first) {              
                if (min_distances[neighb.second] != INF) {
                    vertexes_set.erase(Vertex{min_distances[neighb.second], neighb.second});
                }
                min_distances[neighb.second] = min_distances[nearest.second] + neighb.first;
                vertexes_set.insert(Vertex{min_distances[neighb.second], neighb.second});
            } 
        }
    }
    if (min_distances[finish] == INF) {
        return -1;
    }
    return min_distances[finish];
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
                graph[i].push_back(Vertex{weight, j});
            }
        }
    }
    int answer = dijkstra(n, start, finish, graph);
    std::cout << answer;
}