#include <cstdint>
#include <iostream>
#include <vector>

struct Edge {
  int from;
  int to;
  int64_t weight;
};

using Graph = std::vector<std::vector<int>>;

const int64_t INF = -1e18;

void bfs(int now, std::vector<bool> &used, const Graph& graph) {
    used[now] = true;
    if (now == used.size() - 1) {
        return;
    }
    for (int neighb : graph[now]) {
        if (!used[neighb]) {
            bfs(neighb, used, graph);
        }
    }
}

void bfs_reversed(int now, std::vector<bool> &used, const Graph& graph) {
    used[now] = true;
    if (now == 0) {
        return;
    }
    for (int neighb : graph[now]) {
        if (!used[neighb]) {
            bfs(neighb, used, graph);
        }
    }
}

int ford_bellman(int n, std::vector<int64_t> &max_distances,
                 const std::vector<Edge> &edges,
                 const Graph& graph, const Graph& reversed_graph) {
  max_distances[0] = 0;

  bool is_changed = false;

  for (size_t i = 0; i < n; ++i) {
    is_changed = false;
    for (auto [from, to, weight] : edges) {
      if (max_distances[from] + weight > max_distances[to]) {
        max_distances[to] = max_distances[from] + weight;
        is_changed = true;
      }
    }
    if (!is_changed) {
      break;
    }
  }
  std::vector<bool> used(n);
  bfs(0, used, graph);
  std::vector<bool> used_reversed(n);
  bfs_reversed(n - 1, used_reversed, reversed_graph);
  int vertex = -1;
  for (auto [from, to, weight] : edges) {
    if (used[from] && used_reversed[from] &&
        max_distances[from] + weight > max_distances[to]) {
      max_distances[to] = max_distances[from] + weight;
      vertex = to;
    }
  }
  return vertex;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<Edge> edges;
  Graph graph(n);
  Graph reversed_graph(n);
  for (size_t j = 0; j < m; ++j) {
    int start, end;
    int64_t weight;
    std::cin >> start >> end >> weight;
    --start;
    --end;
    edges.push_back(Edge{start, end, weight});
    graph[start].push_back(end);
    reversed_graph[end].push_back(start);
  }
  std::vector<int64_t> max_distances(n, INF);
  int vertex = ford_bellman(n, max_distances, edges, graph, reversed_graph);
  if (vertex != -1) {
    std::cout << ":)";
    return 0;
  }
  if (max_distances[n - 1] < -1e16) {
    std::cout << ":(";
    return 0;
  }
  std::cout << max_distances[n - 1];
}