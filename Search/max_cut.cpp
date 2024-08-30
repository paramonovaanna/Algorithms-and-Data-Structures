#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

class MaxGraphCut {
public:
  MaxGraphCut(int n) {
    size = n;

    graph.resize(n, std::vector<int>(n));
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < n; ++j) {
        std::cin >> graph[i][j];
      }
    }

    colored.resize(n);
  }

  void update_answer(std::vector<int> left, std::vector<int> right) {
    int cut = 0;
    for (size_t i = 0; i < left.size(); ++i) {
        for (size_t j = 0; j < right.size(); ++j) {
            cut += graph[left[i]][right[j]];
        }
    }

    if (cut < max_cut_size) {
        return;
    }

    max_cut_size = cut;
    for (int vertex : left) {
        colored[vertex] = 1;
    }
    for (int vertex : right) {
        colored[vertex] = 2;
    }
  }

  void calculate(int to_add, std::vector<int> left, std::vector<int> right) {
    if (to_add < size) {
        left.push_back(to_add);
        calculate(to_add + 1, left, right);
        left.pop_back();

        right.push_back(to_add);
        calculate(to_add + 1, left, right);
        return;
    }

    update_answer(left, right);
  }

  void get() {
    std::vector<int> left;
    std::vector<int> right;
    calculate(0, left, right);

    std::cout << max_cut_size << '\n';
    for (int color : colored) {
        std::cout << color << " ";
    }
  }

private:
  int size = 0;
  int max_cut_size = -1e9;
  Graph graph;
  std::vector<int> colored;
};

int main() {
  int n;
  std::cin >> n;

  MaxGraphCut max_graph_cut(n);
  max_graph_cut.get();
}