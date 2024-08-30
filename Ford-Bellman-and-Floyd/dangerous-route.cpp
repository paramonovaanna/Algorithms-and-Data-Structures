#include <iomanip>
#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<double>>;

const double INF = 2.0;

void floyd(int n, Graph& graph) {
    for (size_t k = 0; k < n; ++k) {
        for (size_t from = 0; from < n; ++from) {
            for (size_t to = 0; to < n; ++to) {
                if (graph[from][k] == INF || graph[k][to] == INF) {
                    continue;
                } 
                double new_p = graph[from][k] + (1 - graph[from][k]) * graph[k][to];
                graph[from][to] = std::min(new_p, graph[from][to]);
            }
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    int start, end;
    std::cin >> start >> end;
    --start;
    --end;

    Graph graph(n, std::vector<double>(n, INF));
    for (size_t i = 0; i < n; ++i) {
        graph[i][i] = 0;
    }
    for (size_t i = 0; i < m; ++i) {
        int from, to;
        double probability;
        std::cin >> from >> to >> probability;
        --from;
        --to;
        graph[from][to] = probability / 100;
        graph[to][from] = probability / 100;
    }

    floyd(n, graph);
    std::cout <<  std::setprecision(3) << graph[start][end];
}