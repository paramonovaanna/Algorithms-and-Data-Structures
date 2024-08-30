#include <algorithm>
#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;
using Level = std::vector<std::vector<int>>;

class Dynasty {
public:
    Dynasty(int size, std::vector<int> numbers) {
        n = size;

        graph.resize(n);
        construct_graph(numbers);

        tin.resize(n);
        levels.resize(n);
        tout.resize(n);
        depths.resize(n, -1);

        time = 1;
        dfs(root, 0);
    }

    void construct_graph(std::vector<int> numbers) {
        for (size_t i = 0; i < n; ++i) {
            if (numbers[i] == -1) {
                root = i;
                continue;
            }
            --numbers[i];
            graph[numbers[i]].push_back(i);
            graph[i].push_back(numbers[i]);
        }
    }

    void dfs(int now, int level) {
        depths[now] = level;
        tin[now] = time;
        ++time;

        levels[level].push_back(now);
        for (int neighb : graph[now]) {
            if (depths[neighb] == -1) {
                dfs(neighb, level + 1);
            }
        }
        tout[now] = time;
        ++time;
    }

    int children_amount(int vertex, int k) {
        int level = depths[vertex] + k;
        auto iter1 = std::lower_bound(levels[level].begin(), levels[level].end(), tin[vertex]);
        if (iter1 == levels[level].end()) {
            return 0;
        }
        auto iter2 = std::upper_bound(levels[level].begin(), levels[level].end(), tout[vertex]);
        return iter2 - iter1;
    }

private:
    int n;
    int root;
    int time;
    std::vector<int> tin;
    std::vector<int> tout;
    std::vector<std::vector<int>> levels;
    std::vector<int> depths;
    Graph graph;
};

int main() {
    int n;
    std::cin >> n;

    std::vector<int> numbers(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    Dynasty dynasty(n, numbers);

    int m;
    std::cin >> m;
    for (size_t i = 0; i < m; ++i) {
        int v, k;
        std::cin >> v >> k;
        --v;
        std::cout << dynasty.children_amount(v, k) << "\n";
    }
}
