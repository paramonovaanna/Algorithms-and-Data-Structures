#include <iostream>
#include <vector>
#include <queue>

using Graph = std::vector<std::vector<int>>;
using Cave = std::vector<std::vector<std::vector<bool>>>;

std::vector<int> bfs(int start, int n, const Graph &graph) {
    std::vector<bool> visited(n * n * n);
    std::vector<int> distances(n * n * n, n * n * n + 1);
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
    int n;
    std::cin >> n;
    
    Cave cave(n);
    int position = 0;

    for (size_t i = 0; i < n; ++i) {
        std::vector<std::vector<bool>> level(n);
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                char c;
                std::cin >> c;
                if (c == '#') {
                    level[j].push_back(false);
                } else if (c == '.') {
                    level[j].push_back(true);
                } else {
                    level[j].push_back(true);
                    position = i * n * n + j * n + k;
                }
            }
        }
        cave[i] = level;
    }

    std::vector<int> exits;
    Graph graph(n * n * n);
    for (size_t level = 0; level < n; ++level) {
        for (size_t row = 0; row < n; ++row) {
            for (size_t col = 0 ; col < n; ++col) {
                int vertex = level * n * n + row * n + col;
                if (cave[level][row][col]) {
                    if (level == 0) {
                        exits.push_back(level * n * n + row * n + col);
                    }
                    if (level > 0 && cave[level - 1][row][col]) {
                        graph[vertex].push_back((level - 1) * n * n + row * n + col);
                    }
                    if (level < n - 1 && cave[level + 1][row][col]) {
                        graph[vertex].push_back((level + 1) * n * n + row * n + col);
                    }
                    if (col > 0 && cave[level][row][col - 1]) {
                        graph[vertex].push_back(level * n * n + row * n + (col - 1));
                    }
                    if (col < n - 1 && cave[level][row][col + 1]) {
                        graph[vertex].push_back(level * n * n + row * n + (col + 1));
                    }
                    if (row > 0 && cave[level][row - 1][col]) {
                        graph[vertex].push_back(level * n * n + (row - 1) * n + col);
                    }
                    if (row < n - 1 && cave[level][row + 1][col]) {
                        graph[vertex].push_back(level * n * n + (row + 1) * n + col);
                    }
                }
            }
        }
    }
    std::vector<int> distances = bfs(position, n, graph);
    int answer = 2 * n * n * n;
    for (int exit : exits) {
        answer = std::min(distances[exit], answer);
    }
    std::cout << answer;
}