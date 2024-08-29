#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;


bool dfs(int now, int color, std::vector<int>& colored, const Graph& graph) {
    colored[now] = color;
    bool status;
    for (int neighb : graph[now]) {
        if (colored[neighb] == color) {
            status = true;
            break;
        }
        if (!colored[neighb]) {
            status = dfs(neighb, 3 - color, colored, graph);
        }
    }
    return status;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);
    
    for (size_t i = 0; i != m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        
        --v1;
        --v2;

        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    bool impossible = false;
    std::vector<int> colored(n);

    for (size_t i = 0; i != n; ++i) {
        if (impossible) {
            break;
        }
        if (!colored[i]) {
            impossible = dfs(i, 1, colored, graph);
        }
    }
    if (!impossible) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
}