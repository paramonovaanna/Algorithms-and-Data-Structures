#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>

using number = uint64_t;
using table = std::vector<std::vector<number>>;

class RMQ {
public:
  RMQ(std::vector<number> array, number size) {
    n = size;
    data = array;
    sparse_table.resize(std::floor(std::log2(n)) + 1, std::vector<number>(n));
    build();
    calculate_powers();
  }

  void build() {
    for (size_t col = 0; col < n; ++col) {
      sparse_table[0][col] = data[col];
    }

    for (size_t row = 1; (1 << row) <= n; ++row) {
      for (size_t col = 0; (col + (1 << row) - 1) < n; ++col) {
        sparse_table[row][col] =
            std::min(sparse_table[row - 1][col],
                     sparse_table[row - 1][col + (1 << (row - 1))]);
      }
    }
  }

  void calculate_powers() {
    length_power.resize(n + 1);
    number power = 0;
    for (number length = 1; length <= n; ++length) {
      while ((1 << power) <= length) {
        ++power;
      }
      length_power[length] = power - 1;
    }
  }

  number get_min(number left, number right) {
    number length = right - left + 1;
    number index = length_power[length];
    return std::min(sparse_table[index][left], sparse_table[index][right - (1 << index) + 1]);
  }

private:
  table sparse_table;
  number n;
  std::vector<number> data;
  std::vector<number> length_power;
};

int main() {
  number n, m, a;
  std::cin >> n >> m >> a;

  std::vector<number> nums(n);
  number a2 = a;
  for (size_t i = 0; i < n; ++i) {
    if (i > 0) {
      a = (23 * a + 21563) % 16714589;
    }
    nums[i] = a;
  }
  RMQ rmq(nums, n);

  number u, v;
  std::cin >> u >> v;
  number answer;
  for (size_t i = 1; i < m + 1; ++i) {
    if (i > 1) {
      u = (17 * u + 751 + answer + 2 * (i - 1)) % n + 1;
      v = (13 * v + 593 + answer + 5 * (i - 1)) % n + 1;
    }
    answer = rmq.get_min(std::min(u - 1, v - 1), std::max(u - 1, v - 1));
  }
  std::cout << u << ' ' << v << ' ' << answer;
}