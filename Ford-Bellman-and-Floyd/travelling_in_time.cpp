#include <iostream>
#include <vector>

struct Trip {
    int vertex_from;
    int vertex_to;
    int time_go;
    int time_arrive;
};

const int INF = 1e9;

std::vector<int> ford_bellman(int n, int m, int start, std::vector<Trip> &edges) {
    std::vector<int> min_distances(n, INF);
    min_distances[start] = 0;

    bool is_changed = false;
    for (size_t i = 0; i < m; ++i) {
        is_changed = false;
        for (auto [from, to, time_go, time_arrive] : edges) {
            if (min_distances[from] <= time_go) {
                if (time_arrive < min_distances[to]) {
                    min_distances[to] = time_arrive;
                    is_changed = true;
                }
            }
        }
        if (!is_changed) {
            break;
        }
    }
    return min_distances;
}

int main() {
    int n, start, end;
    std::cin >> n >> start >> end;
    --start;
    --end;

    int m;
    std::cin >> m;
    std::vector<Trip> edges;
    for (size_t i = 0; i < m; ++i) {
        Trip trip;
        std::cin >> trip.vertex_from >> trip.time_go >> trip.vertex_to >> trip.time_arrive;
        --trip.vertex_from;
        --trip.vertex_to;
        edges.push_back(trip);
    }

    std::vector<int> min_distances = ford_bellman(n, m, start, edges);
    std::cout << min_distances[end];
}