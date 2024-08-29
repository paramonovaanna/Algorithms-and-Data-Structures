#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void dfs(int now, std::vector<int> &result, const Graph &graph) {
  result[now] = 1;
  for (int neighb : graph[now]) {
    if (!result[neighb]) {
      dfs(neighb, result, graph);
      result[now] += result[neighb];
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  int m = n - 1;
  Graph graph(n);

  for (size_t i = 0; i != m; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;

    --v1;
    --v2;

    graph[v1].push_back(v2);
    graph[v2].push_back(v1);
  }

  std::vector<int> result(n);

  dfs(0, result, graph);

  for (size_t i = 0; i != n; ++i) {
    std::cout << result[i] << ' ';
  }
}
