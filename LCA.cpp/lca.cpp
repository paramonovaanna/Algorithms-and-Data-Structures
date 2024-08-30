#include <iostream>
#include <vector>
#include <cstdint>


using vertex = int64_t;
using number = int64_t;
using numbers = std::vector<number>;
using Graph = std::vector<numbers>;
using Table = std::vector<numbers>;

void build_parents(number n, Table& parents) {
    for (number i = 1; (1 << i) <= n; ++i) {
        for (number j = 0; j < n; ++j) {
            parents[i][j] = parents[i - 1][parents[i - 1][j]];
        }
    }
}

void dfs(vertex now, numbers& depth, const Graph& graph) {
    for (vertex neighb : graph[now]) {
        if (depth[neighb] == -1) {
            depth[neighb] = depth[now] + 1;
            dfs(neighb, depth, graph);
        }
    }
}

vertex even_levels(vertex v, number difference, const Table& parents) {
    vertex result = v;
    for (int i = parents.size() - 1; i >= 0 && difference > 0; --i) {
        if ((1 << i) > difference) {
            continue;
        }
        result = parents[i][result];
        difference -= (1 << i);
    }
    return result;
}

vertex lca(vertex v1, vertex v2, const numbers& depth, const Table& parents) {
    number level_v1 = depth[v1];
    number level_v2 = depth[v2];
    if (level_v1 < level_v2) {
        v2 = even_levels(v2, level_v2 - level_v1, parents);
    } else if (level_v1 > level_v2) {
        v1 = even_levels(v1, level_v1 - level_v2, parents);
    }

    if (v1 == v2) {
        return v1;
    }
    for (number i = parents.size() - 1; i >= 0; --i) {
        if (parents[i][v1] == parents[i][v2]) {
            continue;
        }
        v1 = parents[i][v1];
        v2 = parents[i][v2];
    }
    return parents[0][v1];
}


int main() {
    number n, m;
    std::cin >> n >> m;

    Graph graph(n);
    Table parents(std::__lg(n) + 1, numbers(n));

    vertex root = 0;
    parents[0][root] = root;

    for (size_t i = 1; i < n; ++i) {
        vertex v;
        std::cin >> v;
        parents[0][i] = v;
        graph[i].push_back(v);
        graph[v].push_back(i);
    }

    build_parents(n, parents);

    numbers depth(n, -1);
    depth[root] = 0;
    dfs(root, depth, graph);

    number a1, a2;
    std::cin >> a1 >> a2;

    number x, y, z;
    std::cin >> x >> y >> z;

    number previous = 0;
    number result = 0;
    for (size_t i = 0; i < m; ++i) {
        if (i > 0) {
            a1 = ((x * a1) % n + (y * a2) % n + z % n) % n;
            a2 = ((x * a2) % n + (y * a1) % n + z % n) % n;
        }
        previous = lca((a1 + previous) % n, a2, depth, parents);
        result += previous;
    }

    std::cout << result;
}