#include <iostream>
#include <vector>

using GraphType = std::vector<std::vector<int>>;

class Graph {
public:
  Graph(int n, int m) : n(n), m(m) { graph.resize(n); }

  void add_edge(int v1, int v2) {
    --v1;
    --v2;
    graph[v1].push_back(v2);
    graph[v2].push_back(v1);
  }

  void dfs(int now, bool is_root) {
    visited[now] = true;
    ++time;
    tin[now] = time;
    for (auto neig : graph[now]) {
      if (!visited[neig]) {
        ++childs[now];
        dfs(neig, false);
        up[now] = std::min(up[now], up[neig]);
        if (up[neig] >= tin[now] && !is_root) {
          articulation_points[now] = true;
        }
      } else {
        up[now] = std::min(up[now], tin[neig]);
      }
    }
  }

  void print_articulation_points() {
    tin.resize(n);
    articulation_points.resize(n);
    visited.resize(n);
    childs.resize(n);
    up.assign(n, n + 1);
    for (size_t now = 0; now != n; ++now) {
      if (!visited[now]) {
        dfs(now, true);
        if (childs[now] >= 2) {
            articulation_points[now] = true;
        }
      }
    }
    std::vector<int> answer;
    for (size_t i = 0; i != n; ++i) {
      if (articulation_points[i]) {
        answer.push_back(i + 1);
      }
    }
    std::cout << answer.size()<< std::endl;
    for (int x : answer) {
        std::cout << x << std::endl;
    }
  }

private:
  int n = 0;
  int m = 0;
  GraphType graph;

  int time = 0;
  std::vector<int> tin;

  std::vector<bool> articulation_points;
  std::vector<bool> visited;
  std::vector<int> childs;
  std::vector<int> up;
};

int main() {
  int n, m;
  std::cin >> n >> m;

  Graph graph(n, m);

  for (size_t i = 0; i != m; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;

    graph.add_edge(v1, v2);
  }

  graph.print_articulation_points();
}