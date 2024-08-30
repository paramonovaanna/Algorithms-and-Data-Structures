#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void dfs(int now, std::vector<bool> &visited, const Graph &graph, std::vector<int> &reversed_order) {
    visited[now] = true;
    for (int neighb : graph[now]) {
        if (!visited[neighb]) {
            dfs(neighb, visited, graph, reversed_order);
        }
    }
    reversed_order.push_back(now);
}

std::vector<int> get_reversed_order(int n, const Graph &graph) {
    std::vector<bool> visited(n);
    std::vector<int> reversed_order;
    for (size_t i = 0; i != n; ++i){
        if (!visited[i]) {
            dfs(i, visited, graph, reversed_order);
        }
    }
    return reversed_order;
}

void dfs_color(int now, int color, std::vector<int> &colored, std::vector<int> &component, const Graph &reversed_graph) {
    colored[now] = color;
    component.push_back(now);
    for (int neighb : reversed_graph[now]) {
        if (!colored[neighb]) {
            dfs_color(neighb, color, colored, component, reversed_graph);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);
    Graph reversed_graph(n);
    std::vector<std::pair<int, int>> edges;

    for (size_t i = 0; i != m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        --v1;
        --v2;
        graph[v1].push_back(v2);
        reversed_graph[v2].push_back(v1);

        edges.push_back(std::pair(v1, v2));
    }

    std::vector<int> reversed_order = get_reversed_order(n, graph);

    int colors = 0;
    std::vector<std::vector<int>> components;
    std::vector<int> colored(n);
    for (size_t i = 0; i != n; ++i) {
        if (!colored[reversed_order[n - i - 1]]) {
            ++colors;
            std::vector<int> component;
            dfs_color(reversed_order[n - i - 1], colors, colored, component, reversed_graph);
            components.push_back(component);
        }
    }

    Graph cond_graph(colors);
    for (std::pair<int, int> edge : edges) {
        if (colored[edge.first] != colored[edge.second]) {
            cond_graph[colored[edge.first] - 1].push_back(colored[edge.second] - 1);
        }
    }
    
    std::vector<int> reversed_order_cond = get_reversed_order(colors, cond_graph);

    std::vector<int> result_colored(n);
    for (size_t i = 0; i != colors; ++i) {
        for (size_t j = 0; j != components[reversed_order_cond[colors - i - 1]].size(); ++j) {
            result_colored[components[reversed_order_cond[colors - i - 1]][j]] = i;
        } 
    }

    std::cout << colors << std::endl;
    for (int color : result_colored) {
        std::cout << color + 1 << ' ';
    }
}