#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>


using Graph = std::vector<std::vector<int>>;

std::vector<int> bfs(std::vector<int> starts, int n, const Graph &graph) {
  std::vector<int> distances(n, -1);
  std::queue<int> vertexes;

  for (int line : starts) {
    vertexes.push(line);
    distances[line] = 0;
  }

  while (!vertexes.empty()) {
    int now = vertexes.front();
    vertexes.pop();

    for (int neighb : graph[now]) {
      if (distances[neighb] == -1) {
        distances[neighb] = distances[now] + 1;
        vertexes.push(neighb);
      }
    }
  }
  return distances;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  std::unordered_map<int, std::vector<int>> stations_data;
  Graph graph(m + 1);
  for (size_t line_now = 0; line_now < m; ++line_now) {
    int station_num;
    std::cin >> station_num;
    for (size_t i = 0; i < station_num; ++i) {
      int station;
      std::cin >> station;
      --station;
      for (int line : stations_data[station]) {
        graph[line_now].push_back(line);
        graph[line].push_back(line_now);
      }
      stations_data[station].push_back(line_now);
    }
  }

  int start, end;
  std::cin >> start >> end;
  --start;
  --end;
  for (int line : stations_data[start]) {
    graph[m].push_back(line);
    graph[line].push_back(m);
  }

  std::vector<int> distances = bfs(stations_data[start], m, graph);
  int answer = m * m * m;
  for (int line : stations_data[end]) {
    if (distances[line] == -1) {
        continue;
    }
    answer = std::min(distances[line], answer);
  }
  if (answer == m * m * m) {
    std::cout << -1;
    return 0;
  }
  std::cout << answer;
}