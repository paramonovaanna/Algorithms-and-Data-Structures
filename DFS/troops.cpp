#include <algorithm>
#include <iostream>
#include <vector>

struct Square {
  int height;
  int x;
  int y;
};

bool squares_comp(const Square &lv, const Square &rv) {
  return lv.height < rv.height;
}

bool accessible_coord(const Square &sq1, const Square &sq2) {
  return std::abs(sq1.x - sq2.x) <= 1 && sq1.y == sq2.y ||
         std::abs(sq1.y - sq2.y) <= 1 && sq1.x == sq2.x;
}

void dfs(int now, int n, int m, std::vector<int> &visited, const std::vector<Square> &squares) {
  visited[squares[now].x * m + squares[now].y] = 1;

  for (size_t i = 0; i != n * m; ++i) {
    if (i == now) {
      continue;
    }
    if (!visited[squares[i].x * m + squares[i].y]) {
      if (squares[i].height >= squares[now].height) {
        if (accessible_coord(squares[now], squares[i])) {
          dfs(i, n, m, visited, squares);
        }
      }
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<Square> squares;
  for (int x = 0; x != n; ++x) {
    for (int y = 0; y != m; ++y) {
      int height;
      std::cin >> height;
      Square square{height, x, y};
      squares.push_back(square);
    }
  }
  std::sort(squares.begin(), squares.end(), squares_comp);
  int components;
  std::vector<int> visited(n * m);
  for (size_t i = 0; i != n * m; ++i) {
    if (!visited[squares[i].x * m + squares[i].y]) {
      ++components;
      dfs(i, n, m, visited, squares);
    }
  }
  std::cout << components;
}