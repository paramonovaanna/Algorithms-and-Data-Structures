#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

struct Edge {
  int weight;
  int from_vertex;
  int to_vertex;
};

bool comp(const Edge &lv, const Edge &rv) {
  return std::tie(lv.weight, lv.from_vertex, lv.to_vertex) <
         std::tie(rv.weight, rv.from_vertex, rv.to_vertex);
}

using Edges = std::vector<Edge>;
using Indexes = std::vector<size_t>;

const int INF = std::numeric_limits<int>::max() / 2;

class DisjointSetUnion {
  using Vertexes = std::vector<int>;
  using Ranks = std::vector<int>;

public:
  DisjointSetUnion(int n) {
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

  Edges edges(m);
  for (int i = 0; i < m; ++i) {
    int v1, v2, weight;
    std::cin >> v1 >> v2 >> weight;
    --v1;
    --v2;
    edges[i] = {weight, v1, v2};
  }

  std::sort(edges.begin(), edges.end(), comp);
  DisjointSetUnion dsu(n);

  Indexes mst_indexes;
  int mstWeight = 0;

  for (size_t ind = 0; ind < m; ++ind) {
    if (dsu.find(edges[ind].from_vertex) != dsu.find(edges[ind].to_vertex)) {
      dsu.unite(edges[ind].from_vertex, edges[ind].to_vertex);
      mstWeight += edges[ind].weight;
      mst_indexes.push_back(ind);
    }
  }

  int secondBestWeight = INF;
  for (size_t index : mst_indexes) {
    Edges new_edges = edges;
    new_edges.erase(new_edges.begin() + index);

    int vertexes_added = 0;
    
    DisjointSetUnion dsu2(n);
    int new_weight = 0;

    for (size_t i = 0; i < m - 1; ++i) {
      if (dsu2.find(new_edges[i].from_vertex) != dsu2.find(new_edges[i].to_vertex)) {
        new_weight += new_edges[i].weight;
        ++vertexes_added;
        dsu2.unite(new_edges[i].from_vertex, new_edges[i].to_vertex);
      }
    }
    if (vertexes_added == n - 1)
      secondBestWeight = std::min(secondBestWeight, new_weight);
  }
  std::cout << mstWeight << ' ' << secondBestWeight;
}
