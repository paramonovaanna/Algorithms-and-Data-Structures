#include <iostream>
#include <vector>
#include <queue>

using Graph = std::vector<std::vector<int>>;

int bfs(int start, int end, int n, const Graph &graph) {
    std::vector<bool> visited(n);
    std::vector<int> distances(n, n + 1);
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
    
    if (visited[end]) {
        return distances[end];
    }
    return -1;
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

  int answer = bfs(start, end, n, graph);
  std::cout << answer;
}