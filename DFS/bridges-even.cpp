#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void dfs(int now, std::vector<int> &subtrees, const Graph &graph) {
  subtrees[now] = 1;
  for (int neighb : graph[now]) {
    if (!subtrees[neighb]) {
      dfs(neighb, subtrees, graph);
      subtrees[now] += subtrees[neighb];
    }
  }
}

int main() {
    int n;
    std::cin >> n;

    Graph graph(n);
    for (size_t i = 0; i != n - 1; ++i) {
        int v1, v2;

        std::cin >> v1 >> v2;
        --v1;
        --v2;

        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    std::vector<int> subtrees(n);
    dfs(0, subtrees, graph);

    int answer = -1;
    for (size_t i = 0; i != n; ++i) {
        if (graph[i].size() == 1) {
            continue;
        }
        bool status = true;
        if (n == 1) {
            status = false;
        }

        if (i == 0) {
            for (size_t i = 0; i != graph[0].size(); ++i) {
                if (subtrees[graph[0][0]] != subtrees[graph[0][i]]) {
                    status = false;
                    break;
                }
            }
        } else {
            for (int neighb : graph[i]) {
                if (subtrees[neighb] > subtrees[i]) {
                    continue;
                }
                if (subtrees[neighb] != n - subtrees[i]) {
                    status = false;
                    break;
                }
            }
        }
        if (status) {
            answer = i + 1;
            break;
        }
    }
    std::cout << answer;
}