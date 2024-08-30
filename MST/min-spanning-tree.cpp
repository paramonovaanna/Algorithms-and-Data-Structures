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
        ranks[second_leader] = std::max(ranks[second_leader], ranks[first_leader] + 1);
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
  for (size_t i = 0; i < m; ++i) {
    std::cin >> edges[i].from_vertex >> edges[i].to_vertex >> edges[i].weight;
    --edges[i].from_vertex;
    --edges[i].to_vertex;
  }

  std::sort(edges.begin(), edges.end(), comp);

  DSU dsu(n);
  Edges mst;
  for (const Edge &edge : edges) {
    if (dsu.find(edge.from_vertex) != dsu.find(edge.to_vertex)) {
        dsu.unite(edge.from_vertex, edge.to_vertex);
        mst.push_back(edge);
    }
  }

  int answer = 0;
  for (const Edge &edge : mst) {
    answer += edge.weight;
  }
  std::cout << answer;
}