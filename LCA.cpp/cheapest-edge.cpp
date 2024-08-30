#include <iostream>
#include <vector>

const int INF = 1e9;

struct Parent {
  size_t vertex;
  int min_weight;
};
using Depths = std::vector<int>;
using Graph = std::vector<std::vector<int>>;
using Table = std::vector<std::vector<Parent>>;

void build_parents(int n, Table &parents) {
  for (int i = 1; (1 << i) <= n; ++i) {
    for (int j = 0; j < n; ++j) {
      parents[i][j].vertex = parents[i - 1][parents[i - 1][j].vertex].vertex;
      int a = parents[i - 1][j].min_weight;
      int b = parents[i - 1][parents[i - 1][j].vertex].min_weight;
      parents[i][j].min_weight =
          std::min(parents[i - 1][j].min_weight,
                   parents[i - 1][parents[i - 1][j].vertex].min_weight);
    }
  }
}

void dfs(int now, Depths &depths, const Graph &graph) {
  for (int neighb : graph[now]) {
    if (depths[neighb] == -1) {
      depths[neighb] = depths[now] + 1;
      dfs(neighb, depths, graph);
    }
  }
}

std::pair<int, int> even_levels(int v, int difference, const Table &parents) {
  int result_vertex = v;
  int result_min_weight = INF;
  for (int i = parents.size() - 1; i >= 0 && difference > 0; --i) {
    if ((1 << i) > difference) {
      continue;
    }
    result_min_weight =
        std::min(result_min_weight, parents[i][result_vertex].min_weight);
    result_vertex = parents[i][result_vertex].vertex;
    difference -= (1 << i);
  }
  return std::pair{result_vertex, result_min_weight};
}

int lca_min_weight(int v1, int v2, const Depths &depths, const Table &parents) {
  if (v1 == v2) {
    return 0;
  }
  int level_v1 = depths[v1];
  int level_v2 = depths[v2];

  int min_weight = INF;
  if (level_v1 < level_v2) {
    auto pair = even_levels(v2, level_v2 - level_v1, parents);
    v2 = pair.first;
    min_weight = pair.second;
  } else if (level_v1 > level_v2) {
    auto pair = even_levels(v1, level_v1 - level_v2, parents);
    v1 = pair.first;
    min_weight = pair.second;
  }

  if (v1 == v2) {
    return min_weight;
  }
  for (int i = parents.size() - 1; i >= 0; --i) {
    if (parents[i][v1].vertex == parents[i][v2].vertex) {
      continue;
    }
    min_weight = std::min(std::min(min_weight, parents[i][v1].min_weight),
                          parents[i][v2].min_weight);
    v1 = parents[i][v1].vertex;
    v2 = parents[i][v2].vertex;
  }
  return std::min(std::min(min_weight, parents[0][v1].min_weight), parents[0][v2].min_weight);
}

int main() {
  int n;
  std::cin >> n;

  Graph graph(n);
  Table parents(std::__lg(n) + 1, std::vector<Parent>(n));

  size_t root = 0;
  parents[0][root] = Parent{root, INF};

  for (size_t i = 1; i < n; ++i) {
    size_t vertex;
    int weight;
    std::cin >> vertex >> weight;
    --vertex;
    parents[0][i] = Parent{vertex, weight};
    graph[i].push_back(vertex);
    graph[vertex].push_back(i);
  }

  build_parents(n, parents);

  Depths depths(n, -1);
  depths[root] = 0;
  dfs(root, depths, graph);

  int m;
  std::cin >> m;
  for (size_t i = 0; i < m; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;
    --v1;
    --v2;
    int lca_result = lca_min_weight(v1, v2, depths, parents);
    std::cout << lca_result << "\n";
  }
}