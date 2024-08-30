#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int weight;
  size_t from_vertex;
  size_t to_vertex;
};

bool comp(const Edge &ls, const Edge &rs) { return ls.weight < rs.weight; }

using Edges = std::vector<Edge>;
using Vertexes = std::vector<int>;
using Ranks = std::vector<int>;

class DSU {
public:
  DSU(int n) {
    leaders.resize(n);
    ranks.resize(n);
    for (size_t i = 0; i < n; ++i) {
      leaders[i] = i;
      ranks[i] = 1;
    }
  }

  int find(int vertex) {
    if (leaders[vertex] == vertex) {
      return vertex;
    }
    leaders[vertex] = find(leaders[vertex]);
    return leaders[vertex];
  }

  void unite(int v1, int v2) {
    int first_leader = find(v1);
    int second_leader = find(v2);
    if (ranks[first_leader] > ranks[second_leader]) {
      std::swap(first_leader, second_leader);
    }
    ranks[second_leader] =
        std::max(ranks[second_leader], ranks[first_leader] + 1);
    leaders[first_leader] = second_leader;
  }

private:
  Vertexes leaders;
  Ranks ranks;
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Edges edges;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
        int status;
        std::cin >> status;
        if (status == 0) {
            if (i < n - 1) {
                edges.push_back(Edge{1, i * m + j, (i + 1) * m + j});
            }
            if (j < m - 1) {
                edges.push_back(Edge{2, i * m + j, i * m + (j + 1)});
            }
        }
        if (status == 1) {
            if (i < n - 1) {
                edges.push_back(Edge{0, i * m + j, (i + 1) * m + j});
            }
            if (j < m - 1) {
                edges.push_back(Edge{2, i * m + j, i * m + (j + 1)});
            }
        } else if (status == 2) {
            if (i < n - 1) {
                edges.push_back(Edge{1, i * m + j, (i + 1) * m + j});
            }
            if (j < m - 1) {
                edges.push_back(Edge{0, i * m + j, i * m + (j + 1)});
            }
        } else if (status == 3) {
            if (i < n - 1) {
                edges.push_back(Edge{0, i * m + j, (i + 1) * m + j});
            }
            if (j < m - 1) {
                edges.push_back(Edge{0, i * m + j, i * m + (j + 1)});
            }
        }
    }
  }

  std::sort(edges.begin(), edges.end(), comp);

  DSU dsu(n * m);
  Edges mst;
  for (const Edge &edge : edges) {
    if (dsu.find(edge.from_vertex) != dsu.find(edge.to_vertex)) {
        dsu.unite(edge.from_vertex, edge.to_vertex);
        if (edge.weight != 0) {
            mst.push_back(edge);
        }
    }
  }

  int answer = 0;
  for (const Edge &edge : mst) {
    answer += edge.weight;
  }
  std::cout << mst.size() << ' ' << answer << '\n';
  for (const Edge &edge : mst) {
    int i = edge.from_vertex / m;
    int j = edge.from_vertex % m;
    int d;
    if (edge.to_vertex == edge.from_vertex + m) {
        d = 1;
    } else {
        d = 2;
    }
    std::cout << i + 1 << ' ' << j + 1 << ' ' << d << '\n';
  }
}