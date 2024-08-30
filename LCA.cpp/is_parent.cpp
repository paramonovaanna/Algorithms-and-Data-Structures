#include <iostream>
#include <vector>

using numbers = std::vector<int>;
using Graph = std::vector<numbers>;
using Table = std::vector<numbers>;

void build_parents(int n, Table& parents) {
    for (int i = 1; (1 << i) <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            parents[i][j] = parents[i - 1][parents[i - 1][j]];
        }
    }
}

void dfs(int now, numbers& depth, const Graph& graph) {
    for (int neighb : graph[now]) {
        if (depth[neighb] == -1) {
            depth[neighb] = depth[now] + 1;
            dfs(neighb, depth, graph);
        }
    }
}

int even_levels(int v, int difference, const Table& parents) {
    int result = v;
    for (int i = parents.size() - 1; i >= 0 && difference > 0; --i) {
        if ((1 << i) > difference) {
            continue;
        }
        result = parents[i][result];
        difference -= (1 << i);
    }
    return result;
}

int lca(int v1, int v2, const numbers& depth, const Table& parents) {
    int level_v1 = depth[v1];
    int level_v2 = depth[v2];
    if (level_v1 < level_v2) {
        v2 = even_levels(v2, level_v2 - level_v1, parents);
    } else if (level_v1 > level_v2) {
        v1 = even_levels(v1, level_v1 - level_v2, parents);
    }

    if (v1 == v2) {
        return v1;
    }
    for (int i = parents.size() - 1; i >= 0; --i) {
        if (parents[i][v1] == parents[i][v2]) {
            continue;
        }
        v1 = parents[i][v1];
        v2 = parents[i][v2];
    }
    return parents[0][v1];
}


int main() {
    int n;
    std::cin >> n;

    int root;
    Graph graph(n);
    Table parents(std::__lg(n) + 1, numbers(n));

    for (size_t i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        if (v == 0) {
            root = i;
            parents[0][i] = root;
        } else {
            --v;
            parents[0][i] = v;
            graph[i].push_back(v);
            graph[v].push_back(i);
        }
    }

    build_parents(n, parents);

    numbers depth(n, -1);
    depth[root] = 0;
    dfs(root, depth, graph);

    int m;
    std::cin >> m;
    for (size_t i = 0; i < m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        --v1;
        --v2;
        int lca_result = lca(v1, v2, depth, parents);
        if (lca_result == v1) {
            std::cout << 1 << "\n";
        } else {
            std::cout << 0 << "\n";
        }
    }
}