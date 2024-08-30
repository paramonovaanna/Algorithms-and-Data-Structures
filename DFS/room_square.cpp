#include <iostream>
#include <vector>

using GraphType = std::vector<std::vector<int>>;

int dfs(int now, std::vector<int> &answer, const GraphType &graph) {
  answer[now] = 1;
  for (int neighb : graph[now]) {
    if (!answer[neighb]) {
      answer[now] += dfs(neighb, answer, graph);
    }
  }
  return answer[now];
}

GraphType construct_graph(int n, const GraphType &labyrinth) {
  GraphType graph(n * n);
  for (size_t x = 0; x < n; ++x) {
    for (size_t y = 0; y < n; ++y) {
      if (labyrinth[x][y] == 1) {
        continue;
      }
      for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
          if (i * j != 0) {
            continue;
          }  
          if (x + i < 0 || x + i >= n) {
            continue;
          }
          if (y + j < 0 || y + j >= n) {
            continue;
          }
          if (labyrinth[x + i][y + j] == 0) {
            graph[x * n + y].push_back((x + i) * n + y + j);
          }
        }
      }
    }
  }
  return graph;
}

int main() {
  int n;
  std::cin >> n;
  GraphType labyrinth(n);
  for (size_t i = 0; i != n; ++i) {
    for (size_t j = 0; j != n; ++j) {
      char symbol;
      std::cin >> symbol;
      if (symbol == '*') {
        labyrinth[i].push_back(1);
      } else {
        labyrinth[i].push_back(0);
      }
    }
  }

  GraphType graph = construct_graph(n, labyrinth);

  int x, y;
  std::cin >> x >> y;
  if (labyrinth[x - 1][y - 1] == 1) {
    std::cout << 0;
  } else {
    int vertex = (x - 1) * n + y - 1;

    std::vector<int> visited(n * n);

    std::cout << dfs(vertex, visited, graph);
  }
}