#include <iostream>
#include <vector>

using number = int;
using table = std::vector<std::vector<number>>;

class BinaryIndexedTree {
public:
  void initialize(number size) {
    n = size;
    tree.resize(n, std::vector<number>(n));
  }

  void inc(number X, number Y, number delta) {
    for (number row = X; row < n; row = (row | (row + 1))) {
      for (number col = Y; col < n; col = (col | (col + 1))) {
        tree[row][col] += delta;
      }
    }
  }

  number prefix_sum(number X, number Y) {
    number result = 0;
    for (number row = X; row >= 0; row = (row & (row + 1)) - 1) {
      for (number col = Y; col >= 0; col = (col & (col + 1)) - 1) {
        result += tree[row][col];
      }
    }
    return result;
  }

  number get_sum(number L, number B, number R, number T) {
    return prefix_sum(R, T) - prefix_sum(L - 1, T) - prefix_sum(R, B - 1) + prefix_sum(L - 1, B - 1);
  }

private:
  table tree;
  number n;
};

int main() {
  BinaryIndexedTree tree;
  number command;
  std::cin >> command;
  while (command != 3) {
    if (command == 0) {
      number s;
      std::cin >> s;
      tree.initialize(s);
    } else if (command == 1) {
      number x, y, a;
      std::cin >> x >> y >> a;
      tree.inc(x, y, a);
      int k = 1;
    } else if (command == 2) {
      number L, B, R, T;
      std::cin >> L >> B >> R >> T;
      std::cout << tree.get_sum(L, B, R, T) << "\n";
    }
    std::cin >> command;
  }
}