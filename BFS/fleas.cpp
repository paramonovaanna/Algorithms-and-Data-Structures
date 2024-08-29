#include <iostream>
#include <queue>
#include <vector>

using Graph = std::vector<std::vector<int>>;

std::vector<int> bfs(int start, int n, const Graph &graph) {
    std::vector<bool> visited(n);
    std::vector<int> distances(n, -1);
    std::queue<int> vertexes;

    vertexes.push(start);
    distances[start] = 0;
    visited[start] = true;

    while (!vertexes.empty()) {
        int now = vertexes.front();
        vertexes.pop();
        
        for (int neighb : graph[now]) {
            if (!visited[neighb]) {
                visited[neighb] = true;
                distances[neighb] = distances[now] + 1;
                vertexes.push(neighb);
            }
        }
    }
    
    return distances;
}

int main() {
    int n, m, food_x, food_y, q;
    std::cin >> n >> m >> food_x >> food_y >> q;
    --food_x;
    --food_y;
    int food = food_x * m + food_y;

    std::vector<std::pair<int, int>> eps = {{-1, -2}, {1, -2}, {1, 2}, {-1, 2}, 
    {-2, -1}, {-2, 1}, {2, 1}, {2, -1}};

    Graph graph(n * m);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            for (auto e : eps) {
                int new_x = i + e.first;
                int new_y = j + e.second;
                if (new_x < 0 || new_x >=n || new_y < 0 || new_y >= m) {
                    continue;
                }
                graph[i * m + j].push_back(new_x * m + new_y);
            }
        }
    }

    std::vector<int> distances = bfs(food, n * m, graph);
    int answer = 0;
    for (size_t i = 0; i < q; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x;
        --y;
        if (distances[x * m + y] == -1) {
            std::cout << -1;
            return 0;
        } 
        answer += distances[x * m + y];
    }
    std::cout << answer;
}