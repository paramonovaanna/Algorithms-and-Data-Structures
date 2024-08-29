#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

struct Apple {
  int x;
  int y;
  int z;
  int radius;
};

bool apples_intersect(const Apple &ap1, const Apple &ap2) {
  return (ap1.z > ap2.z &&
          (ap1.x - ap2.x) * (ap1.x - ap2.x) +
                  (ap1.y - ap2.y) * (ap1.y - ap2.y) <=
              (ap1.radius + ap2.radius) * (ap1.radius + ap2.radius));
}

void dfs(int now, std::vector<bool> &visited, const Graph &graph) {
    visited[now] = true;
    for (size_t i = 0; i != graph.size(); ++i) {
        if (!visited[i] && graph[now][i] == 1) {
            dfs(i, visited, graph);
        }
    }
}

int main() {
  int n;
  std::cin >> n;

  std::vector<Apple> apples(n);
  for (size_t i = 0; i != n; ++i) {
    Apple apple;
    std::cin >> apple.x >> apple.y >> apple.z >> apple.radius;
    apple.z -= apple.radius;
    apples[i] = apple;
  }

  Graph graph(n, std::vector<int>(n, 0));
  for (size_t i = 0; i != n; ++i) {
    for (size_t j = 0; j != n; ++j) {
        if (apples_intersect(apples[i], apples[j])) {
            graph[i][j] = 1;
        }
    }
  }

  std::vector<bool> visited(n);
  dfs(0, visited, graph);

  std::vector<int> answer;
  for (size_t i = 0; i != n; ++i) {
    if (visited[i]) {
        answer.push_back(i + 1);
    }
  }

  std::cout << answer.size() << std::endl;
  for (int vertex : answer) {
    std::cout << vertex << ' ';
  }
}