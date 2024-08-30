#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void dfs(int now, std::vector<int>& comp, std::vector<bool>& visited, const Graph& graph) {
  visited[now] = true;
  comp.push_back(now);
  for (int neighb : graph[now]) {
    if (!visited[neighb]) {
        dfs(neighb, comp, visited, graph);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n);

  for (size_t i = 0; i != m; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;

    --v1;
    --v2;

    graph[v1].push_back(v2);
    graph[v2].push_back(v1);
  }

  std::vector<bool> visited(n);

  Graph components;
  int comp = 0;

  for (size_t i = 0; i != n; ++i) {
    if (!visited[i]) {
      ++comp;

      std::vector<int> comp;
      dfs(i, comp, visited, graph);

      components.push_back(comp);
    }
  }

  std::cout << components.size() << std::endl;


  for (std::vector<int> comp : components) {
    std::cout << comp.size() << std::endl;
    for (size_t j = 0; j != comp.size(); ++j) {
      std::cout << comp[j] + 1 << ' ';
    }
    std::cout << std::endl;
  }
}

