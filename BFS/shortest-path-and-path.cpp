#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using Graph = std::vector<std::vector<int>>;

std::pair<int, std::vector<int>> bfs(int start, int end, int n, const Graph &graph) {
    std::vector<int> distances(n, n + 1);
    std::queue<int> vertexes;
    std::vector<int> path(n, -1);

    vertexes.push(start);
    distances[start] = 0;
    path[start] = start;

    while (!vertexes.empty()) {
        int now = vertexes.front();
        vertexes.pop();
        
        for (int neighb : graph[now]) {
            if (path[neighb] == -1) {
                path[neighb] = now;
                distances[neighb] = distances[now] + 1;
                vertexes.push(neighb);
            }
        }
    }
    
    if (path[end] != -1) {
        return std::pair(distances[end], path);
    }
    return std::pair(-1, path);
}

int main() {
  int n;
  std::cin >> n;

  Graph graph(n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      int edge;
      std::cin >> edge;
      if (edge == 1) {
        graph[i].push_back(j);
      }
    }
  }

  int start, end;
  std::cin >> start >> end;
  --start;
  --end;

  std::pair<int, std::vector<int>> answer = bfs(start, end, n, graph);

  if (answer.first == -1 || answer.first == 0) {
    std::cout << answer.first;
    return 0;
  }

  std::cout << answer.first << std::endl;

  std::vector<int> result_path;
  int v = end;
  while (v != start) {
    result_path.push_back(v);
    v = answer.second[v];
  }
  result_path.push_back(start);

  std::reverse(result_path.begin(), result_path.end());

  for (int vertex : result_path) {
    std::cout << vertex + 1 << ' ';
  }
}