#include <iostream>
#include <queue>
#include <vector>


using Graph = std::vector<std::vector<int>>;

std::vector<int> bfs(int start, int n, const Graph &graph) {
  std::vector<bool> visited(n);
  std::vector<int> distances(n, -1);
  std::queue<int> vertexes;

  vertexes.push(start);
  distances[start] = 0;
  visited[start] = true;

  while (!vertexes.empty()) {
    int now = vertexes.front();
    vertexes.pop();

    for (int neighb : graph[now]) {
      if (!visited[neighb]) {
        visited[neighb] = true;
        distances[neighb] = distances[now] + 1;
        vertexes.push(neighb);
      }
    }
  }
  return distances;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  Graph graph(n);
  std::vector<std::pair<int, int>> edges;
  for (size_t i = 0; i < m; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;
    --v1;
    --v2;
    graph[v1].push_back(v2);
    graph[v2].push_back(v1);
    edges.push_back(std::pair(v1, v2));
  }

  int start, end;
  std::cin >> start >> end;
  --start;
  --end;

  std::vector<int> distances_start = bfs(start, n, graph);
  std::vector<int> distances_end = bfs(end, n, graph);

  int distance = distances_start[end];

  int min_edges = 0;
  for (auto edge : edges) {
    if (distances_start[edge.first] + distances_end[edge.second] ==
            distance - 1 ||
        distances_start[edge.second] + distances_end[edge.first] ==
            distance - 1) {
                min_edges += 1;
            }
  }

  std::cout << m - min_edges;
}