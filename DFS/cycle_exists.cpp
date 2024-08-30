#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void dfs(int now, int previous, std::vector<int>& colored, std::vector<int>& cycle, const Graph& graph) {
    colored[now] = 1;
    for (int neighb : graph[now]) {
        if (neighb != previous && colored[neighb] == 1) {
            cycle.push_back(neighb);
            return;
        }
        if (!colored[neighb]) {
            dfs(neighb, now, colored, cycle, graph);

            if (!cycle.empty() && colored[cycle[0]] != 2) {
                cycle.push_back(neighb);
                colored[now] = 2;
                return;
            }

            if (!cycle.empty() && colored[cycle[0]] == 2) {
                return;
            }
        }
    }
    colored[now] = 2;
}

int main() {
    int n;
    std::cin >> n;

    Graph graph(n);
    
    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != n; ++j) {
            int x;
            std::cin >> x;
            if (x == 1) {
                graph[i].push_back(j);
            }
        }
    }

    std::vector<int> colored(n);
    std::vector<int> cycle;
    for (size_t i = 0; i != n; ++i) {
        if (!cycle.empty()) {
            break;
        }
        if (!colored[i]) {
            dfs(i, -1, colored, cycle, graph);
        }
    }

    if (!cycle.empty()) {
        std::cout << "YES" << std::endl;
        std::cout << cycle.size() << std::endl;
        for (int vert : cycle) {
            std::cout << vert + 1 << ' ';
        }
    } else {
        std::cout << "NO";
    }
}